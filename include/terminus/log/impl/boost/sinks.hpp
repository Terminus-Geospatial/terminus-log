/**************************** INTELLECTUAL PROPERTY RIGHTS ****************************/
/*                                                                                    */
/*                           Copyright (c) 2024 Terminus LLC                          */
/*                                                                                    */
/*                                All Rights Reserved.                                */
/*                                                                                    */
/*          Use of this source code is governed by LICENSE in the repo root.          */
/*                                                                                    */
/***************************# INTELLECTUAL PROPERTY RIGHTS ****************************/
/**
 * @file    sinks.hpp
 * @author  Marvin Smith
 * @date    7/9/2023
*/
#pragma once

// Project Libraries
#include "format.hpp"

// Boost Libraries
#include <boost/algorithm/string/case_conv.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/filesystem/path.hpp>
#include <boost/log/expressions/filter.hpp>
#include <boost/log/sinks/async_frontend.hpp>
#include <boost/log/sinks/sync_frontend.hpp>
#include <boost/log/sinks/text_file_backend.hpp>
#include <boost/log/utility/setup/file.hpp>
#include <boost/log/utility/setup/from_settings.hpp>
#include <boost/shared_ptr.hpp>

// C++ Libraries
#include <stdexcept>
#include <string>

namespace tmns::log::impl::sinks {

/**
 * Utility method for casting a string containing either "true"
 * or "false" into a bool value.
*/
inline bool cast_to_bool( const std::string&     val,
                          const std::string_view name )
{
    auto lval = boost::algorithm::to_lower_copy( val );
    if( lval == "true" )
    {
        return true;
    }
    else if( lval == "false" )
    {
        return false;
    }
    else
    {
        std::string message = "Invalid boolean value for \"";
        message += name;
        message += "\": must be \"true\" or \"false\"";
        throw std::runtime_error( std::move( message ) );
    }
}

/**
 * Creates Sinks that consume log records and write them to a JSON file.
 * The factory is used when the Boost.Log settings file is read and one of
 * the sinks has a Destination field set to "JsonFile".
 *
 * The "JsonFile" sink supports all of the same properties as TextFile sink
 * except the time-based rotation fields.  These are too complicated to replicate.
*/
class Json_File_Sink_Factory : public boost::log::sink_factory<char>
{
    public:

        using SinkBackendType = boost::log::sinks::text_file_backend;

        boost::shared_ptr<boost::log::sinks::sink> create_sink( const settings_section& settings )
        {
            namespace kw = boost::log::keywords;

            // Construct an empty backend
            auto p_sink_backend = boost::make_shared<boost::log::sinks::text_file_backend>();

            // Active file name
            if( boost::optional<std::string> ofile = settings["FileName"] )
            {
                p_sink_backend->set_file_name_pattern( *ofile );
            }
            else
            {
                throw std::runtime_error( R"(Missing "FileName" field in "JsonFile" sink)" );
            }

            // Target file name
            if( boost::optional<std::string> otarget = settings["TargetFileName"])
            {
                p_sink_backend->set_target_file_name_pattern( *otarget );
            }

            // Final Rotation
            if( boost::optional<std::string> enable_final_rot = settings["EnableFinalRotation"] )
            {
                p_sink_backend->enable_final_rotation( cast_to_bool( *enable_final_rot,
                                                                     "EnableFinalRotation" ) );
            }

            // Auto newline mode
            if( boost::optional<std::string> auto_nl = settings["AutoNewline"] )
            {
                const auto& val = *auto_nl;
                if( val == "Disabled" )
                {
                    p_sink_backend->set_auto_newline_mode( boost::log::sinks::disabled_auto_newline );
                }
                else if( val == "AlwaysInsert" )
                {
                    p_sink_backend->set_auto_newline_mode( boost::log::sinks::always_insert );
                }
                else if( val == "InsertIfMissing" )
                {
                    p_sink_backend->set_auto_newline_mode( boost::log::sinks::insert_if_missing );
                }
                else
                {
                    std::string message = "Unsupported auto newline mode \"";
                    message += val;
                    message += "\" in JsonFile configuration";
                    throw std::runtime_error( std::move( message ));
                }
            }

            // Auto flush
            if( boost::optional<std::string> do_auto_flush = settings["AutoFlush"] )
            {
                p_sink_backend->auto_flush( cast_to_bool( *do_auto_flush, "AutoFlush" ) );
            }

            // Append
            if( boost::optional<std::string> do_append = settings["Append"] )
            {
                if( cast_to_bool( *do_append, "Append" ) )
                {
                    p_sink_backend->set_open_mode( std::ios_base::out | std::ios_base::app );
                }
            }

            // Target Directory
            if( boost::optional<std::string> o_target = settings["Target"] )
            {
                boost::filesystem::path target_dir( *o_target );

                // Max Total Size
                uintmax_t max_size = std::numeric_limits<uintmax_t>::max();
                if( boost::optional<std::string> oMaxSize = settings["MaxSize"] )
                {
                    max_size = boost::lexical_cast<uintmax_t>( *oMaxSize );
                }

                // Min Free Space
                uintmax_t space = 0;
                if( boost::optional<std::string> oMinSpace = settings["MinFreeSpace"] )
                {
                    space = boost::lexical_cast<uintmax_t>( *oMinSpace );
                }

                // Max Number of Files
                uintmax_t max_files = std::numeric_limits<uintmax_t>::max();
                if( boost::optional<std::string> oMaxSize = settings["MaxFiles"] )
                {
                    max_files = boost::lexical_cast<uintmax_t>( *oMaxSize );
                }

                p_sink_backend->set_file_collector( boost::log::sinks::file::make_collector(
                    kw::target = target_dir,
                    kw::max_size = max_size,
                    kw::min_free_space = space,
                    kw::max_files = max_files
                ));

                // Scan for log files
                if( boost::optional<std::string> oScanForFiles = settings["ScanForFiles"] )
                {
                    const auto& scanForFiles = *oScanForFiles;
                    if( scanForFiles == "All" )
                    {
                        p_sink_backend->scan_for_files( boost::log::sinks::file::scan_all );
                    }
                    else if( scanForFiles == "Matching" )
                    {
                        p_sink_backend->scan_for_files( boost::log::sinks::file::scan_matching );
                    }
                    else
                    {
                        std::string message = "Unsupported scan method \"";
                        message += scanForFiles;
                        message += "\" in JsonFile configuration";
                       throw std::runtime_error( std::move( message ));
                    }
                }
            }

            // Filter
            boost::log::filter filt;
            if( boost::optional<std::string> oFilter = settings["Filter"] )
            {
                filt = boost::log::parse_filter( *oFilter );
            }

            // Define and configure the sink frontend
            bool async = false;
            if( boost::optional<std::string> oAsync = settings["Asynchronous"])
            {
                async = cast_to_bool( *oAsync, "Asynchronous" );
            }

            if( !async )
            {
                using SinkType = boost::log::sinks::synchronous_sink<SinkBackendType>;
                auto pSink = boost::make_shared<SinkType>( p_sink_backend );
                pSink->set_filter( filt );
                pSink->set_formatter( &format::json );
                return pSink;
            }
            else
            {
                using SinkType = boost::log::sinks::asynchronous_sink<SinkBackendType>;
                auto pSink = boost::make_shared<SinkType>( p_sink_backend );
                pSink->set_filter( filt );
                pSink->set_formatter( &format::json );
                pSink->set_exception_handler( boost::log::nop() );
                return pSink;
            }
        }

}; // End of JSON File Sync Factory


// Register the sync
inline void configure()
{
    boost::log::register_sink_factory( "JsonFile", boost::make_shared<Json_File_Sink_Factory>() );
}

} // End of tmns::log::impl::sinks namespace
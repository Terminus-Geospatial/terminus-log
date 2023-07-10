/**
 * @file    format.hpp
 * @author  Marvin Smith
 * @date    7/9/2023
*/
#pragma once

/**
 * This is a big set of formatter factories we can use to format our
 * attributes.
*/

// Boost Libraries
#include <boost/date_time/posix_time/ptime.hpp>
#include <boost/format.hpp>
#include <boost/json.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/support/date_time.hpp>
#include <boost/log/utility/setup/formatter_parser.hpp>
#include <boost/phoenix/bind.hpp>
#include <boost/shared_ptr.hpp>

// C++ Libraries
#include <iomanip>
#include <string>

namespace tmns::log::impl::format {

/**
 * Formatter for the "Severity" attribute in Boost.Log.  This is a callable object
 * that the `SeverityFormatterFactory` creates so that the user can configure
 * formatting from a format string
*/
class Severity_Formatter
{
    public:

        /**
         * Construct a new formatter instance
         * @param align If true, the string representation of the severity will be left-aligned.
         * @param brackets If true, brackets ("[]") will be inserted around the severity level.
        */
        Severity_Formatter( bool align, bool brackets )
         : m_align{ align }, m_brackets { brackets } {}


        void operator()( boost::log::formatting_ostream&                                    stream,
                         const boost::log::value_ref<boost::log::trivial::severity_level>&  value ) const
        {
            if( value )
            {
                std::string sev = boost::log::trivial::to_string( value.get() );
                if( m_brackets )
                {
                    sev.insert( 0, 1, '[' );
                    sev.push_back( ']' );
                }
                if( m_align )
                {
                    stream << std::left << std::setw(9) << std::setfill(' ') << sev;
                }
                else
                {
                    stream << sev;
                }
            }
        }

    private:

        bool m_align;

        bool m_brackets;

}; // End of Severity_Formatter Class


/**
 * Custom factory for the "Severity" attribute.
*/
class Severity_Formatter_Factory
    : public boost::log::basic_formatter_factory<char, boost::log::trivial::severity_level>
{
    public:
        formatter_type create_formatter( const boost::log::attribute_name& name,
                                         const args_map&                   args )
        {
            namespace expr = boost::log::expressions;
            bool align    = args.find("align") != args.end();
            bool brackets = args.find("brackets") != args.end();
            return boost::phoenix::bind( Severity_Formatter{ align, brackets },
                                         expr::stream,
                                         expr::attr<boost::log::trivial::severity_level>( name )
            );
        }

}; // End of Severity_Formatter_Factory Class

/**
 * Custom formatter for the "TimeStamp" attribute.  This factory enables a user
 * to dynamically specify the format string to use to format the time.
 *
 * The `format` argument, when specified, must be a Boost.DateTime format string.
*/
class Time_Stamp_Formatter_Factory
    : public boost::log::basic_formatter_factory<char,
                                                 boost::posix_time::ptime>
{
    public:

        formatter_type create_formatter( const boost::log::attribute_name& name,
                                         const args_map&                  args )
        {
            namespace expr = boost::log::expressions;
            auto it = args.find( "format" );
            std::string format = it != args.end() ? it->second : R"(%Y-%m-%d %H:%M:%S.%f)";
            return expr::stream << expr::format_date_time<boost::posix_time::ptime>(
                                        expr::attr<boost::posix_time::ptime>( name ), format );
        }

}; // End of Time_Stamp_Formatter_Factory class

/**
 * Formats a Boost.Log record as JSON.  This function is hard-coded to extract only
 * certain attributes from the log record.  See the documentation of Boost.Log support
 * in this library for a complete list of attributes which are supported.
*/
inline void json( boost::log::record_view const&  rec,
                  boost::log::formatting_ostream& stream )
{
    namespace bl = boost::log;

    // Create json object
    boost::json::object json;

    // Capture RecordID
    if( const auto val = bl::extract<uint64_t>( "RecordID", rec ))
    {
        json["RecordID"] = val.get();
    }

    // Capture Severity
    if( const auto val = bl::extract<bl::trivial::severity_level>( "Severity", rec ))
    {
        json["Severity"] = bl::trivial::to_string( val.get() );
    }

    // Capture Message
    if( const auto val = bl::extract<std::string>( "Message", rec ))
    {
        json["Message"] = val.get();
    }

    // Capture TimeStamp
    if( const auto val = bl::extract<boost::posix_time::ptime>( "TimeStamp", rec ))
    {
        const auto& time = val.get();
        json["RecordID"] = boost::posix_time::to_iso_extended_string( time );
    }

    // Capture Scope
    if( const auto val = bl::extract<std::string>( "Scope", rec ))
    {
        json["Scope"] = val.get();
    }

    // Capture ProcessName
    if( const auto val = bl::extract<std::string>( "ProcessName", rec ))
    {
        json["ProcessName"] = val.get();
    }

    // Capture ProcessID
    if( const auto val = bl::extract<std::string>( "ProcessID", rec ))
    {
        json["ProcessID"] = val.get();
    }

    // Capture ThreadID
    if( const auto val = bl::extract<bl::thread_id>( "ThreadID", rec ))
    {
        const auto& threadID = val.get();
        json["ThreadID"] = threadID.native_id();
    }

    // Location Attributes
    if( auto val = bl::extract<std::string>("File", rec))
    {
        json["File"] = val.get();
    }
    if( auto val = bl::extract<int64_t>("Line", rec))
    {
        json["Line"] = val.get();
    }
    if( auto val = bl::extract<std::string>("Function", rec))
    {
        json["Function"] = val.get();
    }

    stream << json;
}

/**
 * Registers our custom formatter factories for the attributes we want to configure
*/
inline void configure()
{
    boost::log::register_formatter_factory(
        "Severity", boost::make_shared<Severity_Formatter_Factory>() );

    boost::log::register_formatter_factory(
        "TimeStamp", boost::make_shared<Time_Stamp_Formatter_Factory>() );
}

} // End of tmns::log::impl::format namespace
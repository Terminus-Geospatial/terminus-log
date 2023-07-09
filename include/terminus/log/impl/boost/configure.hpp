/**
 * @file    configure.hpp
 * @author  Marvin Smith
 * @date    7/8/2023
*/
#pragma once

// Terminus Libraries
#include "attributes.hpp"
#include "format.hpp"
#include "sinks.hpp"

// Boost Libraries
#include <boost/log/expressions.hpp>
#include <boost/log/utility/setup/console.hpp>
#include <boost/log/utility/setup/from_stream.hpp>

// C++ Libraries
#include <filesystem>
#include <fstream>
#include <iostream>

namespace tmns::log::impl::boost {

/**
 * Configures the Boost backend of the library by adding global attributes to the log
 * records and setting up a simple sink that writes to standard error.
*/
inline bool configure()
{
    const std::string FORMAT_STR = R"([%TimeStamp%] %Severity(align=true,brackets=true)%  (%Scope%) %Message%)";
    format::configure();
    boost::log::add_console_log( std::cerr,
                                 boost::log::keywords::format
                                    = FORMAT_STR );
    return attributes::configure();
}

/**
 * Configures the Boost backend of the library using the settings from the
 * stream.  The contents of the stream should be in the format of the Boost.Log
 * `settings.ini` file.
 *
 * @see https://www.boost.org/doc/libs/1_78_0/libs/log/doc/html/log/detailed/utilities.html
 *
 * @param config_stream The stream containing config file information.
 *
 * @returns True if the file is parsed correctly and the library is configured properly.  False
 *          otherwise.
*/
inline bool configure( std::istream& config_stream )
{
    sinks::configure();
    format::configure();
    try
    {
        boost::log::init_from_stream( config_stream );
    }
    catch(const std::exception& e)
    {
        std::cerr << "Failed to load Boost.Log settings: " << e.what() << std::endl;
        return false;
    }
    return attributes::configure();
}

/**
 * Configures the Boost backend of the library using the INI file pointed at by the provided
 * path.  The file must exist and be readable by the process using the log library.
 * `settings.ini` file.
 *
 * @see https://www.boost.org/doc/libs/1_78_0/libs/log/doc/html/log/detailed/utilities.html
 *
 * @param config_path The boost ini file pathname.
 *
 * @returns True if the file is parsed correctly and the library is configured properly.  False
 *          otherwise.
*/
inline bool configure( std::filesystem::path& config_path )
{
    if( !std::filesystem::exists( config_path ) )
    {
        std::cerr << "Boost.Log settings file doesn't exist" << std::endl;
        return false;
    }
    std::ifstream config_stream { config_path };
    if( !config_stream.good() )
    {
        std::cerr << "Failed to open Boost.Log settings file for reading." << std::endl;
        return false;
    }
    return configure( config_stream );
}

} // end of tmns::log::impl::boost namespace
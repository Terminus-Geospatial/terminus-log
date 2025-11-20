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
 * @file    configure.hpp
 * @author  Marvin Smith
 * @date    7/8/2023
*/
#pragma once

/// Terminus Libraries
#include "impl/boost/configure.hpp"

/// C++ Libraries
#include <filesystem>
#include <istream>
#include <string>

namespace tmns::log {

/**
 * Configures the log library backend with reasonable defaults.  At the very least, using
 * this method will produce log records with time, scope, severity level, and message content attached.
 * Additional attributes depend on the backend implementation.
 *
 * @return True if configuration succeeds, false otherwise.
*/
inline bool configure()
{
    return impl::configure();
}

/**
 * Configures the log library using settings read from the stream containing configuration.
 * The format of the content in the stream will depend on the backend requirements.
 *
 * @param config_stream The stream of the configuration settings (usually from file)
 *
 * @return True if the configuration succeeds.  False if the content is not formatted correctly
 * or if the configuration fails in other ways.
*/
inline bool configure( std::istream& config_stream )
{
    return impl::configure( config_stream );
}

/**
 * Configures the log library using settings from the provided configuration file.  The format of
 * the file will depend on the backend requirements.
 *
 * @param config_file_path The path to the configuration file to load.
 *
 * @return True if the configuration succeeds.  False if the content is not formatted correctly
 * or if the configuration fails in other ways.
*/
inline bool configure( const std::filesystem::path& config_file_path )
{
    return impl::configure( config_file_path );
}

inline bool configure( const std::string& config_file_path )
{
    return configure( std::filesystem::path{ config_file_path } );
}

} // End of tmns log namespace
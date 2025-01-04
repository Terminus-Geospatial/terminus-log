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
 * @file    TEST_Boost_JSON_File_Logger.cpp
 * @author  Marvin Smith
 * @date    7/8/2023
 *
 * This shows how to log JSON-formatted records to a file when using the Boost.Log
 * backend.  In this case, you can add a JSON file sink using the Boost.Log config
 * file by adding a sink with a "Destination" of "JsonFile".
*/

// Terminus Libraries
#include <terminus/log/Logger.hpp>
#include <terminus/log/configure.hpp>
#include <terminus/log/utility.hpp>

// C++ Libraries
#include <iostream>

int main()
{
    if( !tmns::log::configure( "logging-json.conf" ) )
    {
        std::cerr << "Failed to configure the logging library" << std::endl;
        return 1;
    }

    // Start logging stuff globally
    tmns::log::trace( tmns::log::loc(), "This is a message logged at 'trace'" );
    tmns::log::debug( tmns::log::loc(), "This is a message logged at 'debug'" );
    tmns::log::info( tmns::log::loc(), "This is a message logged at 'info'" );
    tmns::log::warn( tmns::log::loc(), "This is a message logged at 'warn'" );
    tmns::log::error( tmns::log::loc(), "This is a message logged at 'error'" );
    tmns::log::fatal( tmns::log::loc(), "This is a message logged at 'fatal'" );

    // Sinked Logger
    tmns::log::Logger { "main" };
    logger.trace( tmns::log::loc(), "This is a message logged at 'trace'" );
    logger.debug( tmns::log::loc(), "This is a message logged at 'debug'" );
    logger.info( tmns::log::loc(), "This is a message logged at 'info'" );
    logger.warn( tmns::log::loc(), "This is a message logged at 'warn'" );
    logger.error( tmns::log::loc(), "This is a message logged at 'error'" );
    logger.fatal( tmns::log::loc(), "This is a message logged at 'fatal'" );

    tmns::log::flush();

    return 0;
}
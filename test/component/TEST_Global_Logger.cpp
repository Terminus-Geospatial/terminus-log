/**
 * @file    TEST_Boost_Location_Logger.cpp
 * @author  Marvin Smith
 * @date    7/8/2023
 *
 * This shows how you can attach source location information to your log
 * records.  When logging in this manner, source information will be added
 * as an attribute to your log record if the backend support adding attributes.
 * If your backend does not, then the location will appear in the actual message.
*/

// Terminus Libraries
#include <terminus/log/Logger.hpp>
#include <terminus/log/configure.hpp>
#include <terminus/log/utility.hpp>

// C++ Libraries
#include <iostream>

int main()
{
    if( !tmns::log::configure( "logging-location.conf" ) )
    {
        std::cerr << "Failed to configure the logging library" << std::endl;
        return 1;
    }

    // Start logging stuff globally
    tmns::log::trace( "This is a message logged at 'trace'" );
    tmns::log::debug( "This is a message logged at 'debug'" );
    tmns::log::info( "This is a message logged at 'info'" );
    tmns::log::warn( "This is a message logged at 'warn'" );
    tmns::log::error( "This is a message logged at 'error'" );
    tmns::log::fatal( "This is a message logged at 'fatal'" );

    // Start logging stuff globally
    tmns::log::trace( tmns::log::loc(), "This is a message logged at 'trace'" );
    tmns::log::debug( tmns::log::loc(), "This is a message logged at 'debug'" );
    tmns::log::info( tmns::log::loc(), "This is a message logged at 'info'" );
    tmns::log::warn( tmns::log::loc(), "This is a message logged at 'warn'" );
    tmns::log::error( tmns::log::loc(), "This is a message logged at 'error'" );
    tmns::log::fatal( tmns::log::loc(), "This is a message logged at 'fatal'" );

    tmns::log::info( tmns::log::loc(), "more info, ", 42 );


    return 0;
}
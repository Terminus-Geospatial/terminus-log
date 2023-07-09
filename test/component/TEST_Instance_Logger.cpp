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

    // Sinked Logger
    tmns::log::Logger { "main" };
    logger.trace( "This is a message logged at 'trace'" );
    logger.debug( "This is a message logged at 'debug'" );
    logger.info( "This is a message logged at 'info'" );
    logger.warn( "This is a message logged at 'warn'" );
    logger.error( "This is a message logged at 'error'" );
    logger.fatal( tmns::log::loc(), "This is a message logged at 'fatal'" );

    logger.trace( tmns::log::loc(), "This is a message logged at 'trace'" );
    logger.debug( tmns::log::loc(), "This is a message logged at 'debug'" );
    logger.info( tmns::log::loc(), "This is a message logged at 'info'" );
    logger.warn( tmns::log::loc(), "This is a message logged at 'warn'" );
    logger.error( tmns::log::loc(), "This is a message logged at 'error'" );
    logger.fatal( tmns::log::loc(), "This is a message logged at 'fatal'" );

    logger.info( tmns::log::loc(), "last answer: ", 42 );

    return 0;
}
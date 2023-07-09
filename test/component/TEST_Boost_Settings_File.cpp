/**
 * @file    TEST_Boost_Settings_File.cpp
 * @author  Marvin Smith
 * @date    7/8/2023
 *
 * This test demonstrates the power of using configuration files with
 * Boost.Log to create several sinks and control which log records go to
 * each sink using filters.  The test loads the `logging.conf` file.  See
 * that file to get a description of it's fields.
 *
 * See the boost docs (last section) for more detail
 *
 *      https://www.boost.org/doc/libs/1_82_0/libs/log/doc/html/log/detailed/utilities.html
*/

// Terminus Libraries
#include <terminus/log/Logger.hpp>
#include <terminus/log/configure.hpp>
#include <terminus/log/utility.hpp>

// C++ Libraries
#include <iostream>

/**
 * This class shows how instance loggers (aka "scoped loggers") in the
 * context of this library can be used to log information specific to
 * class.  It also controls how info gets logged.
 *
 * In the `logging.conf` file, look for the sink configured to filter on
 * the `Apple` scope to see where the log records in this class will go.
*/
class Apple
{
    public:

        void process()
        {
            m_logger.info( "Doing some work" );
            m_logger.info( "Doing some more work" );
            m_logger.warn( "That's an odd quirk" );
            m_logger.error( "Ignore this" );
            m_logger.debug( "Random junk" );
            m_logger.info( "All done!" );

        }
    private:

        tmns::log::Logger m_logger{ "Apple" };
}; // end of Apple class

/**
 * This class shows how instance loggers (aka "scoped loggers") in the
 * context of this library can be used to log information specific to
 * class.  It also controls how info gets logged.
 *
 * In the `logging.conf` file, look for the sink configured to filter on
 * the `Orange` scope to see where the log records in this class will go.
*/
class Orange
{
    public:

        void process()
        {
            m_logger.info( "Doing some work" );
            m_logger.info( "Doing some more work" );
            m_logger.warn( "That's an odd quirk" );
            m_logger.error( "Ignore this" );
            m_logger.debug( "Random junk" );
            m_logger.info( "All done!" );

        }
    private:

        tmns::log::Logger m_logger{ "Orange" };
}; // end of Orange class

/**
 * In our `main()` function, we configure the logging library using the
 * Boost.Log config file.  Then we write a bunch of log records and see
 * where they end up.  Note at the end we flush all sinks to prevent leaving
 * something in a buffer.
*/
int main()
{
    if( !tmns::log::configure( "logging.conf" ) )
    {
        std::cerr << "Failed to configure logging." << std::endl;
        return 1;
    }


    tmns::log::warn( "After this message, all other messages will be written using scoped logger." );

    tmns::log::Logger main_logger { "main" };

    main_logger.info( "About to log Apple class." );
    Apple a;
    a.process();

    main_logger.warn( "Not done yet. Still working." );
    main_logger.info( "About to log Orange class." );

    Orange o;
    o.process();

    main_logger.info( "Finished up" );

    tmns::log::flush();

    return 0;
}
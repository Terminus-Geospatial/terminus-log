/**
 * @file    TEST_Logger.cpp
 * @author  Marvin Smith
 * @date    7/8/2023
*/
#include <gtest/gtest.h>

// Terminus Libraries
#include <terminus/log/Logger.hpp>
#include <terminus/log/utility.hpp>

// Test Libraries
#include "Console_Fixture.hpp"

using Logger = Console_Fixture;

/************************************/
/*      Verify the Trace Logger     */
/************************************/
TEST_F( Logger, Log_Trace )
{
    tmns::log::Logger logger{ "test" };
    logger.trace( "Hello, World!" );

    expect_captured( "test" );
    expect_captured( "trace" );
    expect_captured( "Hello, World!" );
}

/************************************/
/*      Verify the Debug Logger     */
/************************************/
TEST_F( Logger, Log_Debug )
{
    tmns::log::Logger logger{ "test" };
    logger.debug( "Hello, World!" );

    expect_captured( "test" );
    expect_captured( "debug" );
    expect_captured( "Hello, World!" );
}

/***********************************/
/*      Verify the Info Logger     */
/***********************************/
TEST_F( Logger, Log_Info )
{
    tmns::log::Logger logger{ "test" };
    logger.info( "Hello, World!" );

    expect_captured( "test" );
    expect_captured( "info" );
    expect_captured( "Hello, World!" );
}

/**************************************/
/*      Verify the Warning Logger     */
/**************************************/
TEST_F( Logger, Log_Warning )
{
    tmns::log::Logger logger{ "test" };
    logger.warn( "Hello, World!" );

    expect_captured( "test" );
    expect_captured( "warn" );
    expect_captured( "Hello, World!" );
}

/************************************/
/*      Verify the Error Logger     */
/************************************/
TEST_F( Logger, Log_Error )
{
    tmns::log::Logger logger{ "test" };
    logger.error( "Hello, World!" );

    expect_captured( "test" );
    expect_captured( "error" );
    expect_captured( "Hello, World!" );
}

/************************************/
/*      Verify the Fatal Logger     */
/************************************/
TEST_F( Logger, Log_Fatal )
{
    tmns::log::Logger logger{ "test" };
    logger.fatal( "Hello, World!" );

    expect_captured( "test" );
    expect_captured( "fatal" );
    expect_captured( "Hello, World!" );
}

/****************************************/
/*          Log Trace Arguments         */
/****************************************/
TEST_F( Logger, Log_Arguments_Trace )
{
    std::string name{ "Joe" };
    tmns::log::Logger logger{ "test" };
    logger.trace( "Hello ", name, ", You have ", 5, " items." );

    expect_captured( "test" );
    expect_captured( "trace" );
    expect_captured( "Hello Joe, You have 5 items." );
}

/****************************************/
/*          Log Debug Arguments         */
/****************************************/
TEST_F( Logger, Log_Arguments_Debug )
{
    std::string name{ "Bob" };
    tmns::log::Logger logger{ "test" };
    logger.debug( "Hello ", name, ", You have ", 8, " items." );

    expect_captured( "test" );
    expect_captured( "debug" );
    expect_captured( "Hello Bob, You have 8 items." );
}

/***************************************/
/*          Log Info Arguments         */
/***************************************/
TEST_F( Logger, Log_Arguments_Info )
{
    std::string name{ "Mary" };
    tmns::log::Logger logger{ "test" };
    logger.info( "Hello ", name, ", You have ", 99, " items." );

    expect_captured( "test" );
    expect_captured( "info" );
    expect_captured( "Hello Mary, You have 99 items." );
}

/******************************************/
/*          Log Warning Arguments         */
/******************************************/
TEST_F( Logger, Log_Arguments_Warning )
{
    std::string name{ "Phil" };
    tmns::log::Logger logger{ "test" };
    logger.trace( "Hello ", name, ", You have ", 77, " items." );

    expect_captured( "test" );
    expect_captured( "warn" );
    expect_captured( "Hello Phil, You have 77 items." );
}

/****************************************/
/*          Log Error Arguments         */
/****************************************/
TEST_F( Logger, Log_Arguments_Error )
{
    std::string name{ "Dan" };
    tmns::log::Logger logger{ "test" };
    logger.trace( "Hello ", name, ", You have ", 3, " items." );

    expect_captured( "test" );
    expect_captured( "error" );
    expect_captured( "Hello Dan, You have 3 items." );
}

/****************************************/
/*          Log Fatal Arguments         */
/****************************************/
TEST_F( Logger, Log_Arguments_Fatal )
{
    std::string name{ "Aaron" };
    tmns::log::Logger logger{ "test" };
    logger.trace( "Hello ", name, ", You have ", 51, " items." );

    expect_captured( "test" );
    expect_captured( "fatal" );
    expect_captured( "Hello Aaron, You have 51 items." );
}

/********************************************/
/*          Log the location as Trace       */
/********************************************/
TEST_F( Logger, Log_Location_Trace )
{
    tmns::log::Logger logger{ "test" };
    logger.trace( tmns::log::loc(), "Hello, World!" );

    expect_captured( "trace" );
    expect_captured( "TEST_Logger.cpp" );
}

/********************************************/
/*          Log the location as Debug       */
/********************************************/
TEST_F( Logger, Log_Location_Debug )
{
    tmns::log::Logger logger{ "test" };
    logger.debug( tmns::log::loc(), "Hello, World!" );

    expect_captured( "debug" );
    expect_captured( "TEST_Logger.cpp" );
}

/*******************************************/
/*          Log the location as Info       */
/*******************************************/
TEST_F( Logger, Log_Location_Info )
{
    tmns::log::Logger logger{ "test" };
    logger.info( tmns::log::loc(), "Hello, World!" );

    expect_captured( "info" );
    expect_captured( "TEST_Logger.cpp" );
}

/**********************************************/
/*          Log the location as Warning       */
/**********************************************/
TEST_F( Logger, Log_Location_Warning )
{
    tmns::log::Logger logger{ "test" };
    logger.warn( tmns::log::loc(), "Hello, World!" );

    expect_captured( "warn" );
    expect_captured( "TEST_Logger.cpp" );
}

/********************************************/
/*          Log the location as Error       */
/********************************************/
TEST_F( Logger, Log_Location_Error )
{
    tmns::log::Logger logger{ "test" };
    logger.error( tmns::log::loc(), "Hello, World!" );

    expect_captured( "error" );
    expect_captured( "TEST_Logger.cpp" );
}

/********************************************/
/*          Log the location as Fatal       */
/********************************************/
TEST_F( Logger, Log_Location_Fatal )
{
    tmns::log::Logger logger{ "test" };
    logger.fatal( tmns::log::loc(), "Hello, World!" );

    expect_captured( "fatal" );
    expect_captured( "TEST_Logger.cpp" );
}


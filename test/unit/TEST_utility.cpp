/**
 * @file    TEST_utility.cpp
 * @author  Marvin Smith
 * @date    7/8/2023
*/
#include "Console_Fixture.hpp"

// Terminus Libraries
#include <terminus/log/utility.hpp>

// GoogleTest
#include <gtest/gtest.h>

using Utility = Console_Fixture;

/********************************/
/*      Test trace logging      */
/********************************/
TEST_F( Utility, log_trace )
{
    tmns::log::trace( "Hello, World!" );
    expect_captured( "trace" );
    expect_captured( "Hello, World!" );
}

/********************************/
/*      Test debug logging      */
/********************************/
TEST_F( Utility, log_debug )
{
    tmns::log::debug( "Hello, World!" );
    expect_captured( "debug" );
    expect_captured( "Hello, World!" );
}

/*******************************/
/*      Test info logging      */
/*******************************/
TEST_F( Utility, log_info )
{
    tmns::log::info( "Hello, World!" );
    expect_captured( "info" );
    expect_captured( "Hello, World!" );
}

/**************************************/
/*      Verify the Warning Logger     */
/**************************************/
TEST_F( Utility, Log_Warning )
{
    tmns::log::warn( "Hello, World!" );
    expect_captured( "warn" );
    expect_captured( "Hello, World!" );
}

/************************************/
/*      Verify the Error Logger     */
/************************************/
TEST_F( Utility, log_error )
{
    tmns::log::error( "Hello, World!" );
    expect_captured( "error" );
    expect_captured( "Hello, World!" );
}

/************************************/
/*      Verify the Fatal Logger     */
/************************************/
TEST_F( Utility, Log_Fatal )
{
    tmns::log::fatal( "Hello, World!" );
    expect_captured( "fatal" );
    expect_captured( "Hello, World!" );
}

/****************************************/
/*          Log Trace Arguments         */
/****************************************/
TEST_F( Utility, Log_Arguments_Trace )
{
    std::string name{ "Joe" };
    tmns::log::trace( "Hello ", name, ", You have ", 5, " items." );
    expect_captured( "trace" );
    expect_captured( "Hello Joe, You have 5 items." );
}

/****************************************/
/*          Log Debug Arguments         */
/****************************************/
TEST_F( Utility, Log_Arguments_Debug )
{
    std::string name{ "Bob" };
    tmns::log::debug( "Hello ", name, ", You have ", 8, " items." );
    expect_captured( "debug" );
    expect_captured( "Hello Bob, You have 8 items." );
}

/***************************************/
/*          Log Info Arguments         */
/***************************************/
TEST_F( Utility, Log_Arguments_Info )
{
    std::string name{ "Mary" };
    tmns::log::trace( "Hello ", name, ", You have ", 99, " items." );
    expect_captured( "info" );
    expect_captured( "Hello Mary, You have 99 items." );
}

/******************************************/
/*          Log Warning Arguments         */
/******************************************/
TEST_F( Utility, Log_Arguments_Warning )
{
    std::string name{ "Phil" };
    tmns::log::trace( "Hello ", name, ", You have ", 77, " items." );
    expect_captured( "warn" );
    expect_captured( "Hello Phil, You have 77 items." );
}

/****************************************/
/*          Log Error Arguments         */
/****************************************/
TEST_F( Utility, Log_Arguments_Error )
{
    std::string name{ "Dan" };
    tmns::log::trace( "Hello ", name, ", You have ", 3, " items." );
    expect_captured( "error" );
    expect_captured( "Hello Dan, You have 3 items." );
}

/****************************************/
/*          Log Fatal Arguments         */
/****************************************/
TEST_F( Utility, Log_Arguments_Fatal )
{
    std::string name{ "Aaron" };
    tmns::log::trace( "Hello ", name, ", You have ", 51, " items." );
    expect_captured( "fatal" );
    expect_captured( "Hello Aaron, You have 51 items." );
}

/********************************************/
/*          Log the location as Trace       */
/********************************************/
TEST_F( Utility, Log_Location_Trace )
{
    tmns::log::trace( tmns::log::loc(), "Hello, World!" );
    expect_captured( "trace" );
    expect_captured( "TEST_Logger.cpp" );
}

/********************************************/
/*          Log the location as Debug       */
/********************************************/
TEST_F( Utility, Log_Location_Debug )
{
    tmns::log::debug( tmns::log::loc(), "Hello, World!" );
    expect_captured( "debug" );
    expect_captured( "TEST_Logger.cpp" );
}

/*******************************************/
/*          Log the location as Info       */
/*******************************************/
TEST_F( Utility, Log_Location_Info )
{
    tmns::log::info( tmns::log::loc(), "Hello, World!" );
    expect_captured( "info" );
    expect_captured( "TEST_Logger.cpp" );
}

/**********************************************/
/*          Log the location as Warning       */
/**********************************************/
TEST_F( Utility, Log_Location_Warning )
{
    tmns::log::warn( tmns::log::loc(), "Hello, World!" );
    expect_captured( "warn" );
    expect_captured( "TEST_Logger.cpp" );
}

/********************************************/
/*          Log the location as Error       */
/********************************************/
TEST_F( Utility, Log_Location_Error )
{
    tmns::log::error( tmns::log::loc(), "Hello, World!" );
    expect_captured( "error" );
    expect_captured( "TEST_Logger.cpp" );
}

/********************************************/
/*          Log the location as Fatal       */
/********************************************/
TEST_F( Utility, Log_Location_Fatal )
{
    tmns::log::fatal( tmns::log::loc(), "Hello, World!" );
    expect_captured( "fatal" );
    expect_captured( "TEST_Logger.cpp" );
}
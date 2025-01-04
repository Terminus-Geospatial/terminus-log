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
 * @file    TEST_Stream_Interceptor.cpp
 * @author  Marvin Smith
 * @date    7/8/2023
*/
#include <gtest/gtest.h>

// Test Libraries
#include "File_Fixture.hpp"

// Terminus Libraries
#include <terminus/log/test/Stream_Interceptor.hpp>

// C++ Libraries
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>

using tmns::log::test::Stream_Interceptor;

using Stream_Interceptor_File = File_Fixture;

/********************************************/
/*      Verify we can capture stdout        */
/********************************************/
TEST( Stream_Interceptor, Capture_Stdout )
{
    auto interceptor = Stream_Interceptor::cout();
    std::cout << "Hello, World!" << std::endl;
    auto contents = interceptor.get_intercepted_contents();
    EXPECT_EQ( contents, "Hello, World!" );
}

/*********************************************************/
/*      Verify we can capture stdout with a functor      */
/*********************************************************/
TEST( Stream_Interceptor, Capture_Stdout_Functor )
{
    auto contents = Stream_Interceptor::capture_stdout(
        [](){ std::cout << "Hello, World!" << std::endl;
    });

   EXPECT_EQ( contents, "Hello, World!" );
}

/********************************************/
/*      Verify we can capture stderr        */
/********************************************/
TEST( Stream_Interceptor, Capture_Stderr )
{
    auto interceptor = Stream_Interceptor::cerr();
    std::cerr << "Hello, World!" << std::endl;
    auto contents = interceptor.get_intercepted_contents();
    EXPECT_EQ( contents, "Hello, World!" );
}

/*********************************************************/
/*      Verify we can capture stderr with a functor      */
/*********************************************************/
TEST( Stream_Interceptor, Capture_Stdcerr_Functor )
{
    auto contents = Stream_Interceptor::capture_stderr(
        [](){ std::cerr << "Hello, World!" << std::endl;
    });

   EXPECT_EQ( contents, "Hello, World!" );
}

/********************************************/
/*      Verify we can capture clog        */
/********************************************/
TEST( Stream_Interceptor, Capture_Stdlog )
{
    auto interceptor = Stream_Interceptor::clog();
    std::clog << "Hello, World!" << std::endl;
    auto contents = interceptor.get_intercepted_contents();
    EXPECT_EQ( contents, "Hello, World!" );
}

/*********************************************************/
/*      Verify we can capture stdlog with a functor      */
/*********************************************************/
TEST( Stream_Interceptor, Capture_Stdlog_Functor )
{
    auto contents = Stream_Interceptor::capture_stdlog(
        [](){ std::clog << "Hello, World!" << std::endl;
    });

   EXPECT_EQ( contents, "Hello, World!" );
}

/************************************************************/
/*          Verify we capture contents written to file      */
/************************************************************/
TEST_F( Stream_Interceptor_File, captures_file_stream )
{
    std::string contents;
    {
        std::ofstream fout{ temp_file() };
        auto interceptor = Stream_Interceptor( fout );
        fout << "Hello, World!" << std::endl;
        contents = interceptor.get_intercepted_contents();
    }

    EXPECT_EQ( contents, "Hello, World!" );

    // Make sure the file is still empty
    std::ifstream fin{ temp_file(), std::ifstream::binary | std::ifstream::ate };
    auto size = fin.tellg();
    EXPECT_EQ( size, 0 );
}
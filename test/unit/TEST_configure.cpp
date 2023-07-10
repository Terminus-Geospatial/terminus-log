/**
 * @file    TEST_configure.cpp
 * @author  Marvin Smith
 * @date    7/8/2023
*/
#include <gtest/gtest.h>

// Terminus Libraries
#include <terminus/log/utility.hpp>

// Project Libraries
#include "File_Fixture.hpp"

using Configure = File_Fixture;

TEST_F( Configure, Log_To_File )
{
    tmns::log::info( "This message should be in the file!" );
    tmns::log::flush();

    expect_file_contains( "This message should be in the file!" );
}
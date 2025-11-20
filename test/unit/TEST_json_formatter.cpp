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
 * @file    TEST_json_formatter.cpp
 * @author  Marvin Smith
 * @date    7/8/2023
 */
#include <gtest/gtest.h>

// C++ Libraries
#include <filesystem>
#include <fstream>
#include <sstream>
#include <string>

// Boost Libraries
#include <boost/json.hpp>

// Terminus Libraries
#include <terminus/log/configure.hpp>
#include <terminus/log/utility.hpp>

TEST( JsonFormatter, BasicJsonContainsCoreAttributes )
{
    namespace fs = std::filesystem;

    // Create a deterministic temporary filename for this test run.
    const auto temp_dir  = fs::temp_directory_path();
    const auto temp_path = temp_dir / "tmns_log_json_unittest.log";

    // Build a minimal Boost.Log settings configuration that uses the JsonFile sink.
    std::string config_contents;
    config_contents  = "[Sinks.Json]\n";
    config_contents += "Destination=JsonFile\n";
    config_contents += "FileName=\"" + temp_path.string() + "\"\n";

    std::istringstream config_stream{ config_contents };
    ASSERT_TRUE( tmns::log::configure( config_stream ) );

    const std::string message{ "Json formatter test message" };

    // Emit a single log record that will be formatted as JSON by the JsonFile sink.
    tmns::log::info( message );
    tmns::log::flush();

    // Read the contents of the generated JSON log file.
    std::ifstream input{ temp_path };
    ASSERT_TRUE( input.good() );

    std::string line;
    std::string last_line;
    while( std::getline( input, line ) )
    {
        if( !line.empty() )
        {
            last_line = line;
        }
    }

    ASSERT_FALSE( last_line.empty() );

    const auto json_value = boost::json::parse( last_line );
    ASSERT_TRUE( json_value.is_object() );

    const auto& obj = json_value.as_object();

    // Core attributes we expect the formatter to emit
    EXPECT_NE( obj.if_contains( "RecordID" ), nullptr );
    EXPECT_NE( obj.if_contains( "TimeStamp" ), nullptr );
    EXPECT_NE( obj.if_contains( "Severity" ), nullptr );
    EXPECT_NE( obj.if_contains( "Message" ), nullptr );

    // Verify the message content is preserved
    ASSERT_TRUE( obj.at( "Message" ).is_string() );
    EXPECT_EQ( obj.at( "Message" ).as_string(), message );

    input.close();
    fs::remove( temp_path );

    // Reset logging back to the default console configuration.
    tmns::log::configure();
}

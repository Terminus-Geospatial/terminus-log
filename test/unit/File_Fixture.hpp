/**
 * @file    File_Fixture.hpp
 * @author  Marvin Smith
 * @date    7/8/2023
*/
#pragma once

// Terminus Libraries
#include <terminus/log/configure.hpp>
#include <terminus/log/utility.hpp>

// GoogleTest Libraries
#include <gmock/gmock.h>
#include <gtest/gtest.h>

// C++ Libraries
#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <sstream>

/**
 * Configures Boost.Log to send log reecords to a unique temp file
*/
class File_Fixture : public testing::Test
{
    protected:

        void SetUp() override
        {
            // Log while we're still a console logger.
            tmns::log::debug( "Setting up File_Fixture" );

            std::srand( static_cast<unsigned int>( reinterpret_cast<std::uintptr_t>( this ) ) );
            int num = std::rand();

            auto temp_dir = std::filesystem::temp_directory_path();

            m_temp_file = temp_dir / ("tmns_log_unittest." + std::to_string( num ) + ".log" );

            // Create the config-file dynamically
            std::string contents{ R"(
                [Sinks.File]
                Destination=TextFile
                Format="%Severity% %Scope% %Message% %File%"
                FileName=)" };

            contents += "\"" + m_temp_file.string() + "\"";
            std::istringstream config{ std::move( contents) };

            // Configure the library to write to our address
            EXPECT_TRUE( tmns::log::configure( config ) );
        }

        void TearDown() override
        {
            std::filesystem::remove( m_temp_file );
            tmns::log::configure();
            tmns::log::debug( "Finished Tearing Down File_Fixture" );
        }

        [[nodiscard]] const std::filesystem::path& temp_file() const
        {
            return m_temp_file;
        }

        void expect_file_contains( const std::string_view content )
        {
            using testing::HasSubstr;
            if( m_contents.empty() )
            {
                std::ifstream input{ m_temp_file };
                if( !input.good() )
                {
                    FAIL() << "Could not open input file to check contents: " << m_temp_file;
                }
                using Iterator = std::istreambuf_iterator<char>;
                m_contents.assign( Iterator{input}, Iterator{} );
            }

            EXPECT_THAT( m_contents, HasSubstr( content.data() ) );
        }

    private:

        std::filesystem::path m_temp_file;
        std::string m_contents;

}; // End of File_Fixture Class
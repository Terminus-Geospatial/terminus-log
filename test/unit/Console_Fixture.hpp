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
 * @file    ConsoleFixture.hpp
 * @author  Marvin Smith
 * @date    7/8/2023
*/
#pragma once

// Terminus Libraries
#include <terminus/log/configure.hpp>
#include <terminus/log/utility.hpp>
#include <terminus/log/test/Stream_Interceptor.hpp>

// GoogleTest Libraries
#include <gmock/gmock.h>
#include <gtest/gtest.h>

// C++ Libraries


/**
 * Configures the Boost.Log backend to write log records to stdlog in a simplified format and
 * captures the contents written to the console.  The fixture also provides a utility member
 * function that makes it easy to check the contents of the captured output for a substring.
*/
class Console_Fixture : public testing::Test
{
    protected:

        void SetUp() override
        {
            // Log while we're still a console logger.
            std::cout << "Setting up Console_Fixture" << std::endl;
            m_captured_contents = "";
            m_interceptor = std::make_unique<tmns::log::test::Stream_Interceptor>( std::clog );

            std::istringstream config{ R"(
                [Sinks.Console]
                Destination=Console
                Format="[%TimeStamp%] %Severity% %Scope% %File% %Message%"
            )" };
            EXPECT_TRUE( tmns::log::configure( config ) );
        }

        void TearDown() override
        {
            tmns::log::configure();
            std::cout << "Finished Tearing Down Console_Fixture" << std::endl;
            m_interceptor.reset();
        }

        void expect_captured( const std::string_view contents )
        {
            if( m_captured_contents.empty() )
            {
                m_captured_contents = m_interceptor->get_intercepted_contents();
            }
            EXPECT_THAT( m_captured_contents, testing::HasSubstr( contents.data() ) );
        }

    private:

        std::unique_ptr<tmns::log::test::Stream_Interceptor> m_interceptor;
        std::string m_captured_contents;

}; // End of Console_Fixture Class
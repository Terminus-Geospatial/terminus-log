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
 * @file    Stream_Interceptor.hpp
 * @author  Marvin Smith
 * @date    7/9/2023
*/
#pragma once

// C++ Includees
#include <iostream>
#include <sstream>
#include <string>

namespace tmns::log::test {

/**
 * Utility class that allows the user to intercept writes to a stream and view the contents.
 * This is particularly useful when capturing the stdout/stderr/stdclog during unit-tests.
 * Any `std::ostream` can be intercepted by this class, although there are a few static helper
 * functions available to make creating interceptors and capturing content simpler.
 *
 * The intercepted contents of the stream passed to the constructor can be obtained using the
 * `get_intercepted_contents()` member function.
 *
 * Once an instance of this class destructs, the stream it was capturing will be restored
 * to it's previous state.
*/
class Stream_Interceptor : public std::streambuf
{
    public:

        /**
         * Create a streeam interceptor which captures anything given to `std::cout`.
        */
        [[nodiscard]] static Stream_Interceptor cout()
        {
            return Stream_Interceptor{ std::cout };
        }

        /**
         * Create a streeam interceptor which captures anything given to `std::cerr`.
        */
        [[nodiscard]] static Stream_Interceptor cerr()
        {
            return Stream_Interceptor{ std::cerr };
        }

        /**
         * Create a streeam interceptor which captures anything given to `std::clog`.
        */
        [[nodiscard]] static Stream_Interceptor clog()
        {
            return Stream_Interceptor{ std::clog };
        }

        /**
         * Captures whatever is written to `std::cout` during invocation of the provided
         * functor and returns the intercepted contents.  No arguments are passed to the
         * functor when it is invoked by this function.
         *
         * @param func Function to invoke.
         * @returns The intercepted contents from `std::cout`.
        */
        template <class CallableT>
        [[nodiscard]] static std::string capture_stdout( CallableT&& func )
        {
            auto interceptor = Stream_Interceptor::cout();
            func();
            return interceptor.get_intercepted_contents();
        }

        /**
         * Captures whatever is written to `std::cerr` during invocation of the provided
         * functor and returns the intercepted contents.  No arguments are passed to the
         * functor when it is invoked by this function.
         *
         * @param func Function to invoke.
         * @returns The intercepted contents from `std::cerr`.
        */
        template <class CallableT>
        [[nodiscard]] static std::string capture_stderr( CallableT&& func )
        {
            auto interceptor = Stream_Interceptor::cerr();
            func();
            return interceptor.get_intercepted_contents();
        }

        /**
         * Captures whatever is written to `std::clog` during invocation of the provided
         * functor and returns the intercepted contents.  No arguments are passed to the
         * functor when it is invoked by this function.
         *
         * @param func Function to invoke.
         * @returns The intercepted contents from `std::clog`.
        */
        template <class CallableT>
        [[nodiscard]] static std::string capture_stdlog( CallableT&& func )
        {
            auto interceptor = Stream_Interceptor::clog();
            func();
            return interceptor.get_intercepted_contents();
        }

        /**
         * Construct a new instance that will intercept writes to the provided output
         * stream.  This effectively replaces the underlying buffer of the provided stream
         * with the one used by the internal `std::ostringstream`.
         *
         * @param stream The stream to intercept
        */
        Stream_Interceptor( std::ostream& stream )
          : m_original_stream{ stream },
            m_orig_buf{ m_original_stream.rdbuf( this ) }
        {
        }

        /**
         * Destructs the instance and restores the original buffer to the stream this instance
         * was constructed with.
        */
        virtual ~Stream_Interceptor()
        {
            m_original_stream.rdbuf( m_orig_buf );
        }

        /**
         * Returns the intercepted contents of writes made to the stream this instance was
         * constructed with.
        */
        [[nodiscard]] std::string get_intercepted_contents() const
        {
            return m_intercepting_stream.str();
        }

    protected:

        std::streamsize xsputn( const char*      msg,
                                std::streamsize  count )
        {
            //Output to new stream with old buffer (to e.g. screen [std::cout])
            m_intercepting_stream.write( msg, count );
            return count;
        }

    private:

        /// The internal stream we use to intercept writes to
        std::stringstream m_intercepting_stream;

        /// Reference to original stream we intercepted
        std::ostream& m_original_stream;

        /// Pointer to the original buffer of the stream we intercepted.
        std::streambuf* m_orig_buf;
        
}; // End of Stream_Interceptor Class

} // End of tmns::log::test namespace
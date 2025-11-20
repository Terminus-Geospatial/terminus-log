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
 * @file    Logger.hpp
 * @author  Marvin Smith
 * @date    7/9/2023
*/
#pragma once

// Terminus Libraries
#include <terminus/log/impl/location.hpp>
#include <terminus/log/impl/boost/utility.hpp>

// Boost Libraries
#include <boost/log/attributes/constant.hpp>
#include <boost/log/sources/severity_logger.hpp>
#include <boost/log/trivial.hpp>

// C++ Libraries
#include <string>

namespace tmns::log::impl {

/**
 * Produces the log records using a single Boost.Log severity logger.  The severity
 * logger is not the multi-threaded version, so a single instance of this implementation
 * should not be used across multiple threads.  This follows the threading guaranteees by
 * the `tmns::log::Logger` class.
 *
 * Each log record produced by this backend implementation assigns it's scope to the "Scope"
 * attribute on a Boost.Log record.  This attribute can be used during filtering.
*/
class Logger
{
    public:

        /**
         * Creates a copy of the logger at the requested scope.
        */
        Logger( std::string scope )
        {
            typedef boost::log::attributes::constant<std::string> attr_const;
            m_logger.add_attribute( "Scope", attr_const( std::move( scope ) ) );
        }

        /**
         * Create a new log record at the DEBUG level
         */
        template <class... ArgsT>
        void debug( ArgsT&&... args )
        {
            impl::write( m_logger,
                         boost::log::trivial::severity_level::debug,
                         std::forward<ArgsT>( args )... );
        }

        /**
         * Create a new log record at the DEBUG level with location
         */
        template <class... ArgsT>
        void debug( std::source_location loc,
                    ArgsT&&...           args )
        {
            impl::write( m_logger,
                         boost::log::trivial::severity_level::debug,
                         std::move( loc ),
                         std::forward<ArgsT>( args )... );
        }

        /**
         * Create a new log record at the TRACE level
         */
        template <class... ArgsT>
        void trace( ArgsT&&... args )
        {
            impl::write( m_logger,
                         boost::log::trivial::severity_level::trace,
                         std::forward<ArgsT>( args )... );
        }

        /**
         * Create a new log record at the TRACE level with location
         */
        template <class... ArgsT>
        void trace( std::source_location loc,
                    ArgsT&&...           args )
        {
            impl::write( m_logger,
                         boost::log::trivial::severity_level::trace,
                         std::move( loc ),
                         std::forward<ArgsT>( args )... );
        }

        /**
         * Create a new log record at the INFO level
         */
        template <class... ArgsT>
        void info( ArgsT&&... args )
        {
            impl::write( m_logger,
                         boost::log::trivial::severity_level::info,
                         std::forward<ArgsT>( args )... );
        }

        /**
         * Create a new log record at the INFO level with location
         */
        template <class... ArgsT>
        void info( std::source_location loc,
                   ArgsT&&...           args )
        {
            impl::write( m_logger,
                         boost::log::trivial::severity_level::info,
                         std::move( loc ),
                         std::forward<ArgsT>( args )... );
        }

        /**
         * Create a new log record at the WARNING level
         */
        template <class... ArgsT>
        void warn( ArgsT&&... args )
        {
            impl::write( m_logger,
                         boost::log::trivial::severity_level::warning,
                         std::forward<ArgsT>( args )... );
        }

        /**
         * Create a new log record at the WARNING level with location
         */
        template <class... ArgsT>
        void warn( std::source_location loc,
                   ArgsT&&...           args )
        {
            impl::write( m_logger,
                         boost::log::trivial::severity_level::warning,
                         std::move( loc ),
                         std::forward<ArgsT>( args )... );
        }

        /**
         * Create a new log record at the ERROR level
         */
        template <class... ArgsT>
        void error( ArgsT&&... args )
        {
            impl::write( m_logger,
                         boost::log::trivial::severity_level::error,
                         std::forward<ArgsT>( args )... );
        }

        /**
         * Create a new log record at the ERROR level with location
         */
        template <class... ArgsT>
        void error( std::source_location loc,
                    ArgsT&&...           args )
        {
            impl::write( m_logger,
                         boost::log::trivial::severity_level::error,
                         std::move( loc ),
                         std::forward<ArgsT>( args )... );
        }

        /**
         * Create a new log record at the FATAL level
         */
        template <class... ArgsT>
        void fatal( ArgsT&&... args )
        {
            impl::write( m_logger,
                         boost::log::trivial::severity_level::fatal,
                         std::forward<ArgsT>( args )... );
        }

        /**
         * Create a new log record at the FATAL level with location
         */
        template <class... ArgsT>
        void fatal( std::source_location loc,
                    ArgsT&&...           args )
        {
            impl::write( m_logger,
                         boost::log::trivial::severity_level::fatal,
                         std::move( loc ),
                         std::forward<ArgsT>( args )... );
        }

    private:

        // Internal logging instance
        boost::log::sources::severity_logger<boost::log::trivial::severity_level> m_logger;

}; // End of Logger class

} // End of tmns::log::impl namespace
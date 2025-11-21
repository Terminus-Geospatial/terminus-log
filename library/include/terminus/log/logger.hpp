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
 * @file    logger.hpp
 * @author  Marvin Smith
 * @date    7/8/2023
*/
#pragma once

// Terminus Libraries
#include <terminus/log/impl/boost/logger.hpp>
#include <terminus/log/impl/location.hpp>

// C++ Libraries
#include <memory>
#include <string>

namespace tmns::log {

/**
 * Produces scoped log records.  These records can be filtered before being sent to their
 * final destination, usually via the configuration file for the logging backend. The scope
 * can also be used to determine which component produced the log record when looking at log
 * records from multiple components in a single file.
 *
 * There is no guarantee that the backend implementation of this scoped logger is thread safe.
 * A single logger instance should not be used from multiple threads.  Logger instances are cheap,
 * so if you need to log at the same scope in multiple threads, create a different logger for each
 * thread.
*/
class Logger
{
    public:

        /**
         * Constructs a new instances and assigns it to the provided scope.
         */
        Logger() : Logger( "global" )
        {
        }

        /**
         * Constructs a new instances and assigns it to the provided scope.
         */
        Logger( std::string scope ) : m_logger { std::move( scope ) }
        {
        }

        /**
         * @brief Create new log record at the DEBUG severity and log it if it passes filtering.
        */
        template <class... ArgsT>
        void debug( ArgsT&&... args )
        {
            m_logger.debug( std::forward<ArgsT>(args)...);
        }

        /**
         * Log a message using the provided arguments at the DEBUG severity level.  The provided
         * source location will be used to set the location and function name attributes on the log
         * record.
         *
         * The backend implementation may choose to just write the location as part of the message
         * rather than attach it as a separate attribute to the record.  Console the documentation
         * on the supported backends for more information.
         *
         * @param loc The source location of the log statement.
         * @param args The arguments used to construct the message via the output stream operator.
        */
        template <class... ArgsT>
        void debug( std::source_location loc,
                    ArgsT&&...           args )
        {
            m_logger.debug( std::move( loc ),
                            std::forward<ArgsT>(args)...);
        }

        /**
         * @brief Create new log record at the TRACE severity and log it if it passes filtering.
        */
        template <class... ArgsT>
        void trace( ArgsT&&... args )
        {
            m_logger.trace( std::forward<ArgsT>(args)...);
        }

        /**
         * Log a message using the provided arguments at the TRACE severity level.  The provided
         * source location will be used to set the location and function name attributes on the log
         * record.
         *
         * The backend implementation may choose to just write the location as part of the message
         * rather than attach it as a separate attribute to the record.  Console the documentation
         * on the supported backends for more information.
         *
         * @param loc The source location of the log statement.
         * @param args The arguments used to construct the message via the output stream operator.
        */
        template <class... ArgsT>
        void trace( std::source_location loc,
                    ArgsT&&...           args )
        {
            m_logger.trace( std::move( loc ),
                            std::forward<ArgsT>(args)...);
        }

        /**
         * @brief Create new log record at the INFO severity and log it if it passes filtering.
        */
        template <class... ArgsT>
        void info( ArgsT&&... args )
        {
            m_logger.info( std::forward<ArgsT>(args)...);
        }

        /**
         * Log a message using the provided arguments at the INFO severity level.  The provided
         * source location will be used to set the location and function name attributes on the log
         * record.
         *
         * The backend implementation may choose to just write the location as part of the message
         * rather than attach it as a separate attribute to the record.  Console the documentation
         * on the supported backends for more information.
         *
         * @param loc The source location of the log statement.
         * @param args The arguments used to construct the message via the output stream operator.
        */
        template <class... ArgsT>
        void info( std::source_location loc,
                   ArgsT&&...           args )
        {
            m_logger.info( std::move( loc ),
                           std::forward<ArgsT>(args)...);
        }

        /**
         * @brief Create new log record at the WARNING severity and log it if it passes filtering.
        */
        template <class... ArgsT>
        void warn( ArgsT&&... args )
        {
            m_logger.warn( std::forward<ArgsT>(args)...);
        }

        /**
         * Log a message using the provided arguments at the WARNING severity level.  The provided
         * source location will be used to set the location and function name attributes on the log
         * record.
         *
         * The backend implementation may choose to just write the location as part of the message
         * rather than attach it as a separate attribute to the record.  Console the documentation
         * on the supported backends for more information.
         *
         * @param loc The source location of the log statement.
         * @param args The arguments used to construct the message via the output stream operator.
        */
        template <class... ArgsT>
        void warn( std::source_location loc,
                   ArgsT&&...           args )
        {
            m_logger.warn( std::move( loc ),
                           std::forward<ArgsT>(args)...);
        }

        /**
         * @brief Create new log record at the ERROR severity and log it if it passes filtering.
        */
        template <class... ArgsT>
        void error( ArgsT&&... args )
        {
            m_logger.error( std::forward<ArgsT>(args)...);
        }

        /**
         * Log a message using the provided arguments at the ERROR severity level.  The provided
         * source location will be used to set the location and function name attributes on the log
         * record.
         *
         * The backend implementation may choose to just write the location as part of the message
         * rather than attach it as a separate attribute to the record.  Console the documentation
         * on the supported backends for more information.
         *
         * @param loc The source location of the log statement.
         * @param args The arguments used to construct the message via the output stream operator.
        */
        template <class... ArgsT>
        void error( std::source_location loc,
                    ArgsT&&...           args )
        {
            m_logger.error( std::move( loc ),
                            std::forward<ArgsT>(args)...);
        }

        /**
         * @brief Create new log record at the FATAL severity and log it if it passes filtering.
        */
        template <class... ArgsT>
        void fatal( ArgsT&&... args )
        {
            m_logger.fatal( std::forward<ArgsT>(args)...);
        }

        /**
         * Log a message using the provided arguments at the FATAL severity level.  The provided
         * source location will be used to set the location and function name attributes on the log
         * record.
         *
         * The backend implementation may choose to just write the location as part of the message
         * rather than attach it as a separate attribute to the record.  Console the documentation
         * on the supported backends for more information.
         *
         * @param loc The source location of the log statement.
         * @param args The arguments used to construct the message via the output stream operator.
        */
        template <class... ArgsT>
        void fatal( std::source_location loc,
                    ArgsT&&...           args )
        {
            m_logger.fatal( std::move( loc ),
                            std::forward<ArgsT>(args)...);
        }

    private:

        /// Backend logging implementation
        impl::Logger m_logger;

}; // End of Logger class

} // End of tmns::log namespace
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
 * @file    utility.hpp
 * @author  Marvin Smith
 * @date    7/8/2023
*/
#pragma once

// Terminus Libraries
#include <terminus/log/impl/boost/utility.hpp>
#include <terminus/log/impl/location.hpp>

namespace tmns::log {

/**
 * Log a message using the provided arguments at the DEBUG severity level to the global logger.
 *
 * @param args The arguments used to construct the message via the output stream operator.
*/
template <class... ArgsT>
void debug( ArgsT&&... args )
{
    impl::debug( std::forward<ArgsT>( args )... );
}

/*
 * Log a message using the provided arguments at the DEBUG severity level to the global logger.
 * The provided source location will be used to set the location and function name attributes on the log
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
    impl::debug( std::move( loc ), std::forward<ArgsT>( args )... );
}

/**
 * Log a message using the provided arguments at the TRACE severity level to the global logger.
 *
 * @param args The arguments used to construct the message via the output stream operator.
*/
template <class... ArgsT>
void trace( ArgsT&&... args )
{
    impl::trace( std::forward<ArgsT>( args )... );
}

/*
 * Log a message using the provided arguments at the TRACE severity level to the global logger.
 * The provided source location will be used to set the location and function name attributes on the log
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
    impl::trace( std::move( loc ), std::forward<ArgsT>( args )... );
}

/**
 * Log a message using the provided arguments at the INFO severity level to the global logger.
 *
 * @param args The arguments used to construct the message via the output stream operator.
*/
template <class... ArgsT>
void info( ArgsT&&... args )
{
    impl::info( std::forward<ArgsT>( args )... );
}

/*
 * Log a message using the provided arguments at the INFO severity level to the global logger.
 * The provided source location will be used to set the location and function name attributes on the log
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
    impl::info( std::move( loc ), std::forward<ArgsT>( args )... );
}

/**
 * Log a message using the provided arguments at the WARNING severity level to the global logger.
 *
 * @param args The arguments used to construct the message via the output stream operator.
*/
template <class... ArgsT>
void warn( ArgsT&&... args )
{
    impl::warn( std::forward<ArgsT>( args )... );
}

/*
 * Log a message using the provided arguments at the DEBUG severity level to the global logger.
 * The provided source location will be used to set the location and function name attributes on the log
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
    impl::warn( std::move( loc ), std::forward<ArgsT>( args )... );
}

/**
 * Log a message using the provided arguments at the ERROR severity level to the global logger.
 *
 * @param args The arguments used to construct the message via the output stream operator.
*/
template <class... ArgsT>
void error( ArgsT&&... args )
{
    impl::error( std::forward<ArgsT>( args )... );
}

/*
 * Log a message using the provided arguments at the ERROR severity level to the global logger.
 * The provided source location will be used to set the location and function name attributes on the log
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
    impl::error( std::move( loc ), std::forward<ArgsT>( args )... );
}

/**
 * Log a message using the provided arguments at the FATAL severity level to the global logger.
 *
 * @param args The arguments used to construct the message via the output stream operator.
*/
template <class... ArgsT>
void fatal( ArgsT&&... args )
{
    impl::fatal( std::forward<ArgsT>( args )... );
}

/*
 * Log a message using the provided arguments at the FATAL severity level to the global logger.
 * The provided source location will be used to set the location and function name attributes on the log
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
    impl::fatal( std::move( loc ), std::forward<ArgsT>( args )... );
}

/**
 * Produces information about the current source location.  This is a convenience function that
 * can be used in combination with any of the other logging-related functions to attach source
 * location information to the log record.
 *
 * @param location The source location.  The default is the current source location, an an actual
 *        argument will rarely need to be supplied manually.
 *
 * @returns the source location passed into the function.  This is just an identity function to make
 * adding source location information easier (fewer characters to type).
*/
inline std::source_location loc( std::source_location location = std::source_location::current() )
{
    return location;
}

/**
 * Blocks to flush all log records to their final destination
*/
inline void flush()
{
    impl::flush();
}

}  // End of tmns::log namespace

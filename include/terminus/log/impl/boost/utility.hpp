/**
 * @file    utility.hpp
 * @author  Marvin Smith
 * @date    7/9/2023
*/
#pragma once

// Project Libraries
#include "../location.hpp"

// Boost Libraries
#include <boost/log/attributes/scoped_attribute.hpp>
#include <boost/log/core.hpp>
#include <boost/log/sources/severity_logger.hpp>
#include <boost/log/trivial.hpp>

// C++ Libraries
#include <filesystem>

namespace tmns::log::impl {

/**
 * Logs a message created from the provided arguments at the specified
 * severity level to the provided logger.
*/
template <class LoggerT, typename... ArgsT>
void write( LoggerT&                            logger,
            boost::log::trivial::severity_level severity,
            ArgsT&&...                          args )
{
    auto rec = logger.open_record( boost::log::keywords::severity = severity );
    if( !!lrec )
    {
        auto pump = boost::log::aux::make_record_pump( logger, rec );
        (pump.stream() << ... << std::forward<ArgsT>( args ) );
    }
}

/**
 * Logs a message created from the provided arguments at the specified
 * severity level to the provided logger.
*/
template <class LoggerT, typename... ArgsT>
void write( LoggerT&                            logger,
            boost::log::trivial::severity_level severity,
            std::source_location                location,
            ArgsT&&...                          args )
{
    std::filesystem::path file{ location.file_name() };
    BOOST_LOG_SCOPED_THREAD_ATTR(
        "File",
        boost::log::attributes::constant<std::string>( file.filename().string() )
    );
    BOOST_LOG_SCOPED_THREAD_ATTR(
        "Line",
        boost::log::attributes::constant<int64_t>( location.line() )
    );
    BOOST_LOG_SCOPED_THREAD_ATTR(
        "Function",
        boost::log::attributes::constant<std::string>( location.line() )
    );
    write( logger, severity, std::forward<ArgsT>( args )... );
}

template <class... ArgsT>
void debug( ArgsT&&... args )
{
    write( boost::log::trivial::logger::get(),
           boost::log::trivial::severity_level::debug,
           std::forward<ArgsT>( args )... );
}

template <class... ArgsT>
void debug( std::source_location loc,
            ArgsT&&...           args )
{
    write( boost::log::trivial::logger::get(),
           boost::log::trivial::severity_level::debug,
           std::move( loc ),
           std::forward<ArgsT>( args )... );
}

template <class... ArgsT>
void trace( ArgsT&&... args )
{
    write( boost::log::trivial::logger::get(),
           boost::log::trivial::severity_level::trace,
           std::forward<ArgsT>( args )... );
}

template <class... ArgsT>
void trace( std::source_location loc,
            ArgsT&&...           args )
{
    write( boost::log::trivial::logger::get(),
           boost::log::trivial::severity_level::trace,
           std::move( loc ),
           std::forward<ArgsT>( args )... );
}

template <class... ArgsT>
void info( ArgsT&&... args )
{
    write( boost::log::trivial::logger::get(),
           boost::log::trivial::severity_level::info,
           std::forward<ArgsT>( args )... );
}

template <class... ArgsT>
void info( std::source_location loc,
            ArgsT&&...           args )
{
    write( boost::log::trivial::logger::get(),
           boost::log::trivial::severity_level::info,
           std::move( loc ),
           std::forward<ArgsT>( args )... );
}

template <class... ArgsT>
void warn( ArgsT&&... args )
{
    write( boost::log::trivial::logger::get(),
           boost::log::trivial::severity_level::warn,
           std::forward<ArgsT>( args )... );
}

template <class... ArgsT>
void warn( std::source_location loc,
            ArgsT&&...           args )
{
    write( boost::log::trivial::logger::get(),
           boost::log::trivial::severity_level::warn,
           std::move( loc ),
           std::forward<ArgsT>( args )... );
}

template <class... ArgsT>
void error( ArgsT&&... args )
{
    write( boost::log::trivial::logger::get(),
           boost::log::trivial::severity_level::error,
           std::forward<ArgsT>( args )... );
}

template <class... ArgsT>
void error( std::source_location loc,
            ArgsT&&...           args )
{
    write( boost::log::trivial::logger::get(),
           boost::log::trivial::severity_level::error,
           std::move( loc ),
           std::forward<ArgsT>( args )... );
}

template <class... ArgsT>
void debug( ArgsT&&... args )
{
    write( boost::log::trivial::logger::get(),
           boost::log::trivial::severity_level::debug,
           std::forward<ArgsT>( args )... );
}

template <class... ArgsT>
void fatal( std::source_location loc,
            ArgsT&&...           args )
{
    write( boost::log::trivial::logger::get(),
           boost::log::trivial::severity_level::fatal,
           std::move( loc ),
           std::forward<ArgsT>( args )... );
}

/**
 * Blocks to flush all log records through all sinks
*/
inline void flush()
{
    boost::log::core::get()->flush();
}

} // End of tmns::log::impl namespace
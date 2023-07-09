/**
 * @file    attributes.hpp
 * @author  Marvin Smith
 * @date    7/8/2023
*/
#pragma once

// Boost Log Libraries
#include <boost/log/attributes.hpp>
#include <boost/log/core.hpp>
#include <boost/log/trivial.hpp>

// C++ Libraries
#include <string>

namespace tmns::log::impl::attributes {

/**
 * Configures the attributes that will be applied to every log record. It also
 * sets up the scope on the global logger.
*/
inline bool configure()
{
    auto log_core = boost::log::core::get();
    log_core->add_global_attribute("RecordID", boost::log::attributes::counter<uint64_t>{1} );
    log_core->add_global_attribute("TimeStamp", boost::log::attributes::utc_clock() );
    log_core->add_global_attribute("ProcessName", boost::log::attributes::current_process_name());
    log_core->add_global_attribute("ProcessID", boost::log::attributes::current_process_id() );
    log_core->add_global_attribute("ThreadID", boost::log::attributes::current_thread_id() );

    /**
     * Scope is weird in that you can't override boost since it messes with threading.  Instead, register
     * the "scope" with the global trivial logger and then add the scope attribute to each severity logger
     * owned by our `tmns::log::impl::Logger` instances.
    */
   auto& logger = boost::log::trivial::logger::get();
   logger.add_attribute("Scope", boost::log::attributes::constant<std::string>("global"));

   return true;
}

} // End of tmns::log::impl::attributes namespace
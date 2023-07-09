/**
 * @file    location.hpp
 * @author  Marvin Smith
 * @date    7/8/2023
*/
#pragma once

/**
 * This flag allows clients of the library to use std::source_location if they
 * support it in the experimental version.  This is not entirely supported yet,
 * so this flag may be necessary.
*/
#ifdef TERMINUS_LOG_ENABLE_EXPERIMENTAL_SOURCE_LOCATION

#include <experimental/source_location>

namespace std
{
    using std::experimental::source_location;
}

#else

#include <source_location>

#endif

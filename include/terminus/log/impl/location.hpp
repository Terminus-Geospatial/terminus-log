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

#elif TERMINUS_LOG_ENABLE_SOURCE_LOCATION_HACK

namespace std
{
class source_location
{
    public:
    static consteval source_location current() noexcept;
    constexpr source_location() noexcept;

    // source location field access
    inline constexpr uint_least32_t line() const noexcept
    {
        return -1;
    }
    constexpr uint_least32_t column() const noexcept;
    inline constexpr const char* file_name() const noexcept
    {
        return "NOT IMPLEMENTED";
    }
    inline constexpr const char* function_name() const noexcept
    {
        return "NOT IMPLEMENTED";
    }
};

}

#else

#include <source_location>

#endif

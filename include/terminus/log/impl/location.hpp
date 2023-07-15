/**
 * @file    location.hpp
 * @author  Marvin Smith
 * @date    7/8/2023
*/
#pragma once

// Terminus Includes
#include "../Exports.hpp"

// C++ Libraries
#include <cstdint>

/**
 * This flag allows clients of the library to use std::source_location if they
 * support it in the experimental version.  This is not entirely supported yet,
 * so this flag may be necessary.
*/
#if TERMINUS_LOG_SOURCE_LOCATION_METHOD == 2

#include <experimental/source_location>

namespace std
{
    using std::experimental::source_location;
}

#elif TERMINUS_LOG_SOURCE_LOCATION_METHOD == 1

namespace std
{
class source_location
{
    public:

        static constexpr source_location current( const uint_least32_t line     = __LINE__,
                                                  const std::string&   filename = __FILE__,
                                                  const std::string&   function = "NOT_IMPLEMENTED" ) noexcept
        {
            std::source_location result;
            result.m_line     = line;
            result.m_file     = filename;
            result.m_function = function;
            return result;
        }

        constexpr source_location() noexcept = default;

        // source location field access
        inline constexpr uint_least32_t line() const noexcept
        {
            return m_line;
        }
        constexpr uint_least32_t column() const noexcept;
        inline constexpr const char* file_name() const noexcept
        {
            return m_file.c_str();
        }
        inline constexpr const char* function_name() const noexcept
        {
            return m_function.c_str();
        }


    private:

        uint_least32_t m_line{};
        //uint_least32_t m_column{};
        std::string m_file { "" };
        std::string m_function { "" };
};

}

#else

#include <source_location>

#endif

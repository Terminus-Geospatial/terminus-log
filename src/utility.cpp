/**
 * @file    utility.cpp
 * @author  Marvin Smith
 * @date    7/16/2023
*/
#include "utility.hpp"

// Terminus Log Libraries
#include "impl/boost/utility.hpp"

namespace tmns::log {

/****************************************/
/*          Get source location         */
/****************************************/
std::source_location loc( std::source_location location )
{
    return location;
}

/****************************************/
/*          Flush to final dest         */
/****************************************/
void flush()
{
    impl::flush();
}

} // end of tmns::log namespace
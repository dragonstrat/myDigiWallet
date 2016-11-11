/*******************************
 * header for utility functions
 * by Ganghee Jang
 *******************************
 */

#ifndef __MY_UTILITY_FUNCTIONS__
#define __MY_UTILITY_FUNCTIONS__

#include <string>
#include <assert.h>
#include <utility>
#include <cstdint>
#include <iostream>
#include <type_traits>
#include <stdexcept>

// return -1 when out of range exception occurs.
// return 0 when fails for wrong format of input transaction
// return 1 when successful
int findFieldData(std::string& linebuffer, int& id1, int& id2);

#endif

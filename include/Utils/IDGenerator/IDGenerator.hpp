/**
 * @file IDGenerator.hpp
 * @author Haziq Sabtu (mhaziq.sabtu@gmail.com)
 * @brief Utils Class for generating unique ID between 10000 - 99999
 * @version 1.0.0
 * @date 2023-03-18
 *
 * @copyright Copyright (c) 2023
 *
 */
#ifndef ID_GENERATOR_HPP
#define ID_GENERATOR_HPP

#include <cstdlib>
#include <ctime>
#include <iostream>

namespace Utils {
class IDGenerator {
  public:
    static int GenerateID() {
        srand(time(NULL));
        int id = rand() % 90000 + 10000;
        return id;
    }
};
} // namespace Utils

#endif
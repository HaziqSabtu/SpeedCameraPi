#ifndef ID_GENERATOR_HPP
#define ID_GENERATOR_HPP

#include <cstdlib>
#include <ctime>
#include <iostream>

class RandomIDGenerator {
  public:
    RandomIDGenerator();
    int generateID();
};

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
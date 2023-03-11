#include <Utils/IDGenerator/IDGenerator.hpp>

RandomIDGenerator::RandomIDGenerator() { srand(time(NULL)); }

int RandomIDGenerator::generateID() {
    int id = rand() % 90000 + 10000;
    return id;
}
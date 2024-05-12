#include "randomInteger.h"
#include <random>
using namespace std;

int randomInteger::random() {
    // Create a random device
    std::random_device rd;

    // Initialize a Mersenne Twister random number generator with the random device
    std::mt19937 gen(rd());

    // Create a distribution - we want integers between 0 and 99 (inclusive)
    std::uniform_int_distribution<> dis(0, 99);
    return dis(gen);
}

int randomInteger::random(int left, int right) {
    // Create a random device
    std::random_device rd;

    // Initialize a Mersenne Twister random number generator with the random device
    std::mt19937 gen(rd());

    // Create a distribution - we want integers between 0 and 99 (inclusive)
    std::uniform_int_distribution<> dis(left, right);
    return dis(gen);
}
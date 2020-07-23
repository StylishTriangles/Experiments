#include "random.hpp"
#include <cstdlib>
#include <random>

static auto rng = xoroshiro128();

std::string random_string(int length, std::string allowed_chars) {
    std::string ret;
    ret.resize(length);

    if (allowed_chars.empty()) {
        for (int i = 0; i < 128; i++) {
            if (isprint(i)) {
                allowed_chars.push_back(i);
            }
        }
    }

    for (int i = 0; i < length; i++) {
        std::uniform_int_distribution<int> ri(0, allowed_chars.size());
        ret[i] = allowed_chars[ri(rng)];
    }
    return ret;
}
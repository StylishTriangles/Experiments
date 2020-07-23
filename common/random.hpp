#pragma once
#include "xoroshiro128.hpp"

#include <vector>
#include <string>

// allowed_chars defaults to all printable characters in range [0,127]
std::string random_string(int length, std::string allowed_chars = {});
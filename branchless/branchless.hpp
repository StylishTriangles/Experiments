#pragma once
#include <string>

void to_upper_inline(std::string& str);
void to_upper_inline_loop(std::string& str);
void to_upper_inline_branchless(std::string& str);

void to_upper_C(char* str, int len);
void to_upper_branchless_C(char* str, int len);

#include <string>


void to_upper_inline(std::string& str) {
    for (auto &c: str) {
        if (c >= 'a' && c <= 'z') {
            c -= 32;
        }
    }
}

void to_upper_inline_loop(std::string& str) {
    for (int i = 0; i < str.size(); i++) {
        if (str[i] >= 'a' && str[i] <= 'z') {
            str[i] -= 32;
        }
    }
}

void to_upper_inline_branchless(std::string& str) {
    for (int i = 0; i < str.size(); i++) {
        str[i] -= 32 * (str[i] >= 'a' && str[i] <= 'z');
    }
}

void to_upper_C(char* str, int len) {
    for (int i = 0; i < len; i++) {
        if (str[i] >= 'a' && str[i] <= 'z')
            str[i] -= 32;
    }
}

void to_upper_branchless_C(char* str, int len) {
    for (int i = 0; i < len; i++) {
        str[i] -= 32 * (str[i] >= 'a' && str[i] <= 'z');
    }
}
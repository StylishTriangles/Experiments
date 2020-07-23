#include <random.hpp>
#include <timer.hpp>
#include <cstdio>
#include <chrono>
#include <cstring>
#include "branchless.hpp"

const int t_size = 100000;
const int t_count = 1000;

using time_unit = std::chrono::microseconds;

void benchmark(const std::string dataset[], void (*func) (std::string&), const std::string& dataset_name, const std::string& func_name) {
    uint64_t min = -1, max = 0, sum = 0;
    for (int i = 0; i < t_count; i++) {
        std::string tested = dataset[i];
        Timer::start();
        // call the tested function
        func(tested);

        auto t = Timer::stop();
        auto t_conv = std::chrono::duration_cast<time_unit>(t);
        uint64_t count = t_conv.count();
        if (count > max)
            max = count;
        if (count < min)
            min = count;
        sum += count;
    }
    printf("%s(set %s): %luus(min) %luus(max) %luus(avg)\n", func_name.c_str(), dataset_name.c_str(), min, max, sum/t_count);
}

void benchmark_C(const char* dataset[], void (*func) (char*, int), const std::string& dataset_name, const std::string& func_name) {
    uint64_t min = -1, max = 0, sum = 0;
    for (int i = 0; i < t_count; i++) {
        char* tested = new char[t_size];
        memcpy(tested, dataset[i], t_size);
        Timer::start();
        // call the tested function
        func(tested, t_size);

        auto t = Timer::stop();
        auto t_conv = std::chrono::duration_cast<time_unit>(t);
        uint64_t count = t_conv.count();
        if (count > max)
            max = count;
        if (count < min)
            min = count;
        sum += count;
        delete[] tested;
    }
    printf("%s(set %s): %luus(min) %luus(max) %luus(avg)\n", func_name.c_str(), dataset_name.c_str(), min, max, sum/t_count);
}

int main() {
    std::string a[t_count];
    std::string b[t_count];
    std::string c[t_count];

    const char* a_c[t_count];
    const char* b_c[t_count];
    const char* c_c[t_count];

    printf("Characters in string: %d, string count per test: %d\n\n", t_size, t_count);
    printf("Generating random datasets... ");
    fflush(stdout);
    for (int i = 0; i < t_count; i++) {
        a[i] = random_string(t_size, "abcdefghijklmnopqrstuvwxyz");
        b[i] = random_string(t_size, "12345!@# abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQR"); // half affected
        c[i] = random_string(t_size); // few affected

        // this is probably illegal in some countries
        a_c[i] = a[i].c_str();
        b_c[i] = b[i].c_str();
        c_c[i] = c[i].c_str();
    }
    printf("done\n");

    benchmark(a, to_upper_inline, "a", "to_upper_inline");
    benchmark(b, to_upper_inline, "b", "to_upper_inline");
    benchmark(c, to_upper_inline, "c", "to_upper_inline");

    benchmark(a, to_upper_inline_loop, "a", "to_upper_inline_loop");
    benchmark(b, to_upper_inline_loop, "b", "to_upper_inline_loop");
    benchmark(c, to_upper_inline_loop, "c", "to_upper_inline_loop");

    benchmark(a, to_upper_inline_branchless, "a", "to_upper_inline_branchless");
    benchmark(b, to_upper_inline_branchless, "b", "to_upper_inline_branchless");
    benchmark(c, to_upper_inline_branchless, "c", "to_upper_inline_branchless");

    benchmark_C(a_c, to_upper_C, "a_c", "to_upper_C");
    benchmark_C(b_c, to_upper_C, "b_c", "to_upper_C");
    benchmark_C(c_c, to_upper_C, "c_c", "to_upper_C");

    benchmark_C(a_c, to_upper_branchless_C, "a_c", "to_upper_branchless_C");
    benchmark_C(b_c, to_upper_branchless_C, "b_c", "to_upper_branchless_C");
    benchmark_C(c_c, to_upper_branchless_C, "c_c", "to_upper_branchless_C");

    return 0;
}
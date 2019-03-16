#include <cstdlib>
#include <cstdio>
#include <chrono>

extern "C" {
    int fun(int);
    int fun2(int);
}

const int sz = 1<<15;
const int iter = 1 << 14; // total number of iterations is equal to sz*iter
const int possibilities[] = {
    20,
    30,
    50,
    70,
    110,
    130,
    170,
    190,
};

int* make_cyclic() {
    int* cyclic = new int[sz];
    for (int i = 0; i < sz; i++) {
        cyclic[i] = possibilities[i%8]; // Cases are accessed one after another
    }
    return cyclic;
}

int* make_random() {
    int* random = new int[sz];
    for (int i = 0; i < sz; i++) {
        random[i] = possibilities[rand()%8]; // ranom brackets bad branch prediction
    }
    return random;
}

int* make_default() {
    int* def = new int[sz];
    for (int i = 0; i < sz; i++) {
        def[i] = rand(); // This will hit default case most of the time
    }
    return def;
}

void run_test(int* arr) {
    typedef std::chrono::high_resolution_clock Clock;
    srand(69);
    unsigned suma1 = 0, suma2 = 0;

    auto t1 = Clock::now();
    for (int i = 0; i < iter; i++) {
        for (int j = 3; j < sz; j+=4) {
            suma1 += fun(arr[j]);
            suma1 += fun(arr[j-1]);
            suma1 += fun(arr[j-2]);
            suma1 += fun(arr[j-3]);
        }
    }
    auto t2 = Clock::now();
    double r1 = double((t2-t1).count())/1e9;

    t1 = Clock::now();
    for (int i = 0; i < iter; i++) {
        for (int j = 3; j < sz; j+=4) {
            suma2 += fun2(arr[j]);
            suma2 += fun2(arr[j-1]);
            suma2 += fun2(arr[j-2]);
            suma2 += fun2(arr[j-3]);
        }
    }
    t2 = Clock::now();
    double r2 = double((t2-t1).count())/1e9;
    printf("%.5f | %.5f | %u\n", r1, r2, (suma1+suma2)%1000007);
}


int main() {
    int * arr;
    arr = make_cyclic();
    printf("Cyclic:  ");
    run_test(arr);
    delete [] arr;

    arr = make_random();
    printf("Random:  ");
    run_test(arr);
    delete [] arr;

    arr = make_default();
    printf("Default: ");
    run_test(arr);
    delete [] arr;
    return 0;
}
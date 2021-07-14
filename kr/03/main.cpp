#include <functional>
#include <iostream>
#include <sstream>
#include <memory>

void calc_binom(int n, int k, std::function<void(uint64_t)> cb) {
    if (k > n || k < 0) {
        cb(0);
    } else if (k == 0) {
        cb(1);
    } else {
        calc_binom(n - 1, k, [n, k, cb](uint64_t a) {
            calc_binom(n - 1, k - 1, [a, cb](uint64_t b) {
                cb(a + b);
            });
        });
    }
}
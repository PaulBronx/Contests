#include <functional>
#include <cstdint>

void calc_binom(int n, int k, std::function<void(uint64_t)> cb) {
    if (n > 0 && k > 0) {
        try {
            calc_binom(-n, -k, cb);
        } catch (uint64_t res) {
            cb(res);
        }
    } else {
        int N = -n, K = -k;

        if (!(-n) || !(-k) || (-n) == (-k)) {
            throw (uint64_t) 1;
        } else {

            uint64_t t1, t2;
            try {
                calc_binom(n + 1, k, cb);
            } catch (uint64_t res) {
                t1 = res;
            }

            try {
                calc_binom(n + 1, k + 1, cb);
            } catch (uint64_t res) {
                t2 = res;
            }

            throw t1 + t2;
        }
    }
}
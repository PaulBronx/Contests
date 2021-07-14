#include <iostream>

namespace Sample {
    template<typename T, const size_t x, const size_t y>
    class Matrix {
        T arr[x * y];
    public:
        T &operator[](size_t iter) {
            return arr + iter * y;
        }

        const T &operator[](size_t iter) const {
            return arr + iter * y;
        }
    };
}
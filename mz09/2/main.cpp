#include <iostream>

class Result
{
    long long val;
public:
    Result(long long result) : val(result) {}

    long long result() const { return val; }
};

void func(long long a, long long b, int k)
{
    if (!k) {
        throw Result{a + b};
    }

    if (k > 0 && b == 1) {
        Result r{a};
        throw r;
    }
    if (k > 0 && b > 1) {
        long long tmp{0};
        try {
            func(a, b - 1, k);
        } catch (Result r) {
            tmp = r.result();
        }
        func(a, tmp, k - 1);
    }
}

int main()
{
    long long a, b;
    int k;
    while (std::cin >> a >> b >> k)
    {
        try {
            func(a, b, k);
        } catch (Result ex) {
            std::cout << ex.result() << std::endl;
        }
    }
}
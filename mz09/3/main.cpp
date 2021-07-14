#include <iostream>

class S
{
    bool r{};
    int n{};
public:
    S()
    {
        r = bool{std::cin >> n};
    }
    S(S&& other) noexcept
    {
        r = bool{std::cin >> n};
        if (r && other.r) {
            other.r = false;
            n += other.n;
        }
    }

    ~S()
    {
        if (r) {
            std::cout << n << std::endl;
        }
    }

    operator bool()
    {
        return r;
    }
};
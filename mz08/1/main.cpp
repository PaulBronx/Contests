#include <iostream>

int main(void)
{
    unsigned long long n, m, r1, c1, r2, c2;
    std::cin >> m >> n;
    while (std::cin >> r1 >> c1 >> r2 >> c2) {
        if (r2 < r1)
        {
            std::swap(r1, r2);
        }
        if (c2 < c1)
        {
            std::swap(c1, c2);
        }

        std::cout << std::min(r2 - r1, r1 + m - r2) +
                std::min(c2 - c1, c1 + n - c2) << std::endl;
    }
    return 0;
}
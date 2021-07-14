#include <iostream>
#include <iomanip>

void pri(int w, int like, int v) {
    std::cout << std::fixed;
    std::cout << std::setprecision(10) <<
    (double) (-1.0 + 2.0 * (like - w) / v);
}

int main() {
    int w1, w2;
    unsigned x;
    int like = 0, dislike = 0, v = 0, pr = 0;
    std::cin >> w1 >> w2;
    while (std::cin >> x) {
        while (x > 0) {
            pr += x & 1;
            x >>= 1;
        }
        v += 32;
        like += pr;
        dislike += 32 - pr;
        pr = 0;
    }

    if (w2 < like) {
        pri(w2, like, v);
        std::cout << ' ';
    } else {
        std::cout << -1 << ' ';
    }

    if (w1 < dislike) {
        pri(-w1, like, v);
        std::cout << std::endl;
    } else {
        std::cout << 1 << std::endl;
    }

    return 0;
}
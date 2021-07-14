#include <iostream>

int main() {
    int k, n, m;
    std::cin >> k;
    if ((k % 2 == 1) || (k < 4)) {
        return 0;
    }
    n = k /2 -1;
    m = k/2 - n;
    while(n > 0){
        rec(n,m);
        n--;
        m++;
    }
    return 0;
}

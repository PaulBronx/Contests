#include <iostream>
#include <map>

int main()
{
    constexpr uint32_t MOD = 4294967161;
    std::map<std::pair<uint32_t, uint32_t>, uint64_t> matr;
    uint32_t r, c;
    uint64_t  key;
    int a = 0;
    while (std::cin >> r >> c >> key) {
        if (!r && !c && key == MOD) {
            a = 1;
        } else {
            if (!a) {
                matr[std::make_pair(r, c)] = key;
            } else {
                matr[std::make_pair(r, c)] += key;
            }
        }
    }

    for (auto& iter : matr) {
        if (iter.second % MOD != 0) {
            std::cout << iter.first.first << ' ' << iter.first.second
            << ' ' << iter.second % MOD << std::endl;
        }
    }
    return 0;
}
#include <iostream>
#include <vector>
#include <cstdint>

void process(const std::vector<uint64_t>& v1,
        std::vector<uint64_t>& v2, int s)
{
    auto v2_i = v2.rbegin();
    for (auto v1_i = std::begin(v1);
        v1_i < std::end(v1) && v2_i != v2.rend(); v1_i += s, ++v2_i) {
        *v2_i += *v1_i;
        if (std::distance(v1_i, std::end(v1)) < s) {
            break;
        }
    }
}
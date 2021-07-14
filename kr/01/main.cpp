#include <iostream>
#include <vector>

void process(std::vector<uint64_t>& v, uint32_t s)
{
    if (v.empty()) {
        return;
    }
    std::vector<uint64_t> cop(v);
    auto iter = v.begin();
    auto final = cop.begin();
    uint64_t sum = 0;
    uint32_t shift = 0;
    uint32_t sz = v.size() / s;
    v.resize(v.size() + sz);
    while (iter != v.end())
    {
        if (shift == s) {
            *iter = sum;
            shift = 0;
            ++iter;
        } else {
            *iter = *final;
            sum += *final;
            ++shift;
            ++iter;
            ++final;
        }
    }
}
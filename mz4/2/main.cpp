#include <vector>

void process(std::vector<long long> &ar, long long limit) {
    if (ar.empty()) {
        return;
    }
    ar.reserve(ar.size() * 2);
    for (auto i = ar.end() - 1; i >= ar.begin(); --i) {
        if (*i >= limit) {
            ar.push_back(*i);
        }
    }
    return;
}
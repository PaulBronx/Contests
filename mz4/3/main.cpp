#include <vector>
#include <algorithm>


void process(const std::vector<int> &v1, std::vector<int> &v2) {
    std::vector<int> cop = v1;
    std::sort(cop.begin(), cop.end());
    cop.erase(std::unique(begin(cop), end(cop)), end(cop));
    auto t = v2.begin();
    auto i = t;
    auto counter = 0;
    auto n = cop.begin();
    while (n != cop.end() && *n < 0) {
        n++;
    }
    while (i != v2.end()) {
        if (n != cop.end() && *n == i - v2.begin()) {
            n++;
            counter++;
        } else {
            std::swap(*t, *i);
            t++;
        }
        i++;
    }
    v2.resize(v2.size()-counter);
}
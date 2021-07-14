#include <algorithm>
#include <set>
#include <iterator>

template<typename It1, typename It2>
It2 myremove(It1 beg1, It1 end1,
        It2 beg2, It2 end2) {
    std::set<int> inds;
    inds.insert(beg1, end1);

    auto ind_it = inds.begin();
    while (ind_it != inds.end() && *ind_it < 0) {
        ++ind_it;
    }

    It2 end;
    int ind{};
    if (ind_it != inds.end()) {
        for (end = beg2; beg2 != end2; ++beg2, ++ind) {
            if (ind_it != inds.end() && ind == *ind_it) {
                ++ind_it;
                continue;
            }
            std::swap(*end, *beg2);
            ++end;
        }
    } else {
        end = end2;
    }

    return end;
}
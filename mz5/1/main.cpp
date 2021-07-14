#include <iterator>

template <typename Container>
typename Container::value_type process(const Container val)
{
    auto it = val.rbegin();
    if (val.size() > 4)
    {
        return *it + *std::next(it, 2) + *std::next(it, 4);
    } else if (val.size() > 2)
    {
        return *it + *std::next(it, 2);
    } else if (!val.empty()) {
        return *it;
    }
    typename Container::value_type def{};
    return def;
}
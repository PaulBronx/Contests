template <typename Container, typename F>
Container myfilter(const Container& val, F func)
{
    Container result{};
    for (auto el : val)
    {
        if (func(el))
        {
            result.insert(result.end(), el);
        }
    }
    return result;
}
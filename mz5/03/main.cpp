#include <vector>
#include <iterator>
#include <functional>

template <typename Iterator, typename Function>
void myapply( Iterator beg, Iterator end, Function f)
{
    for (auto i = beg ; i != end; i++)
    {
        f(*i);
    }
}

template <typename Iterator, typename Function>
std::vector<std::reference_wrapper
        <typename std::iterator_traits<Iterator>::value_type>>
myfilter2(Iterator beg , Iterator end, Function f)
{
    std::vector<std::reference_wrapper
            <typename std::iterator_traits<Iterator>::value_type>> res;

    for (auto i = beg ; i != end; i++)
    {
        if (f(*i))
        {
            res.push_back(*i);
        }
    }

    return res;
}
#include <algorithm>

template <typename T>
class Coord
{
public:
    typedef T value_type;
    T row, col;

    Coord(void) {}
    Coord(T row) : row(row) {}
    Coord(T row, T col) : row(row), col(col) {}
};

template <typename T>
T dist(Coord<T> siz, Coord<T> x, Coord<T> y)
{
    if ( y.row < x.row)
    {
        std::swap(x.row , y.row);
    }
    if ( y.col < x.col)
    {
        std::swap(x.col, y.col);
    }

    T r = std::min(y.row - x.row, x.row + siz.row - y.row);
    T c = std::min(y.col - x.col, x.col + siz.col - y.col);

    return std::max(r, c);
}
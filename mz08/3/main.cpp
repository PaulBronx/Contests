#include <cmath>

namespace Game
{
    template <typename T>
    class Coord
    {
    public:
        typedef T value_type;
        T row{};
        T col{};

        Coord() = default;
        explicit Coord(T row) : row(row) {}
        Coord(T row, T col) : row(row), col(col) {}
    };

    template <typename T>
    T dist(Coord<T> sz, Coord<T> cord_1, Coord<T> cord_2)
    {
        T dx = cord_1.row - cord_2.row;
        T dy = cord_1.col - cord_2.col;
        T dv = 0.866 * dy;
        T du = dx - 0.5 * dy;
        return std::sqrt(du * du + dv * dv);
    }
}
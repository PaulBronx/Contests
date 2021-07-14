#include <string>
#include <sstream>
#include <cmath>

class Rectangle : Figure
{
    double _a, _b;

public:
    double get_square() const override
    {
        return _a * _b;
    }

    static Rectangle* make(std::string s)
    {
        double a, b;
        std::stringstream stream(s);
        stream >> a >> b;

        Rectangle* new_fig = new Rectangle;
        new_fig->_a = a;
        new_fig->_b = b;

        return new_fig;
    }
};

class Square : Figure
{
    double a_;

public:
    double get_square() const override
    {
        return a_ * a_;
    }

    static Square* make(std::string params)
    {
        double a;
        std::stringstream stream(params);
        stream >> a;

        Square* new_fig = new Square;
        new_fig->a_ = a;

        return new_fig;
    }
};

class Circle : Figure
{
    double _r;

public:
    double get_square() const override
    {
        return M_PI * _r * _r;
    }

    static Circle* make(std::string s)
    {
        double r;
        std::stringstream stream(s);
        stream >> r;

        Circle* new_fig = new Circle;
        new_fig->_r = r;

        return new_fig;
    }
};
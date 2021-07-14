#include <iostream>

class Figure{
public:
    Figure() {};

    virtual ~Figure() {};

    virtual bool equals(Figure * other) const = 0;
};

class Rectangle : public Figure {
    int x, y;
public:
    Rectangle(int base = 0, int side = 0) : x(base), y(side) {}

    virtual ~Rectangle() {}

    virtual bool equals(Figure * f) const {
        if (f == nullptr) {
            return false;
        }

        Rectangle oth;
        try{
            oth = dynamic_cast<Rectangle &> (*f);
        } catch (const std::bad_cast& ex) {
            return false;
        }

        return (oth.x == x && oth.y == y);
    }
};

class Triangle : public Figure {
    int x, y, z;
public:
    Triangle(int base = 0, int side_1 = 0, int side_2 = 0)
        : x(base), y(side_1), z(side_2) {}

    virtual ~Triangle() {}

    virtual bool equals(Figure * f) const {
        if (f == nullptr) {
            return false;
        }

        Triangle oth;
        try{
            oth = dynamic_cast<Triangle &> (*f);
        } catch (const std::bad_cast& ex) {
            return false;
        }

        return (oth.x == x && oth.y == y && oth.z == z);
    }
};
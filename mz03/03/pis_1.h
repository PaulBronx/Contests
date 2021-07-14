#include <iostream>
#include <cstdio>
#include <string>
#include <sstream>
#include <cmath>

namespace numbers {
    class complex {
        double re_, im_;

    public:
        complex(const double re = 0., const double im = 0.) : re_(re), im_(im) {}

        explicit complex(std::string str) {
            std::stringstream stream{str};
            stream.ignore(1);
            stream >> re_;
            stream.ignore(1);
            stream >> im_;
        }

        double re() const { return re_; }

        double im() const { return im_; }

        double abs2() const {
            return re_ * re_ + im_ * im_;
        }

        double abs() const {
            return sqrt(re_ * re_ + im_ * im_);
        }

        std::string to_string() const {
            char buf[1024];
            sprintf(buf, "(%.10g,%.10g)", re_, im_);
            return std::string(buf);
        }

        complex operator+=(const complex val) {
            return complex(re_ + val.re_, im_ + val.im_);
        }

        complex operator-=(const complex val) {
            return complex(re_ - val.re_, im_ - val.im_);
        }

        complex operator*=(const complex val) {
            return complex(re_ * val.re_ - im_ * val.im_,
                           re_ * val.im_ + im_ * val.re_);
        }

        complex operator/=(const complex val) {
            double k = val.re_ * val.re_ + val.im_ * val.im_;
            return complex((re_ * val.re_ + im_ * val.im_) / k,
                           (-re_ * val.im_ + im_ * val.re_) / k);
        }

        complex operator~() const {
            return complex(re_, -im_);
        }

        complex operator-() const {
            return complex(-re_, -im_);
        }

        friend complex operator+(const complex val_1, const complex val_2);

        friend complex operator-(const complex val_1, const complex val_2);

        friend complex operator*(const complex val_1, const complex val_2);

        friend complex operator/(const complex val_1, const complex val_2);
    };

    complex operator+(complex val_1, const complex val_2) {
        return (val_1 += val_2);
    }

    complex operator-(complex val_1, const complex val_2) {
        return (val_1 -= val_2);
    }

    complex operator*(complex val_1, const complex val_2) {
        return (val_1 *= val_2);
    }

    complex operator/(complex val_1, const complex val_2) {
        return (val_1 /= val_2);
    }
};
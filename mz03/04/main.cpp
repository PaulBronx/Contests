#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <cmath>

#include "cmc_complex.h"
#include "cmc_complex_stack.h"
#include "cmc_complex_eval.h"

int main(int argc, char const *argv[]) {
    numbers::complex c(argv[1]);
    double r = std::stod(argv[2]);
    int n = std::stoi(argv[3]);
    double s = 2 * M_PI / n;
    std::vector<std::string> args;
    for (int i = 4; argv[i]; ++i) {
        args.push_back(argv[i]);
    }

    numbers::complex result;
    for (int i = 0; i < n; ++i) {
        double angle = (i + 0.5) * s;
        numbers::complex dl{-sin(angle) * s, cos(angle) * s};
        result += numbers::eval(args, c + numbers::complex(
                r * cos(angle), r * sin(angle))) * dl;
    }
    std::cout << result.to_string() << std::endl;
}

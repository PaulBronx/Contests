#include <cinttypes>
#include <iostream>
#include <utility>
#include <map>

void print_matrix(std::map<std::pair<uint32_t, uint32_t>, uint32_t>&matrix) {
    for(auto &[position, value] : matrix) {
        if(value) {
            std::cout << position.first << " " << position.second
                      << " " << value << std::endl;
        }
    }
}

int main() {
    constexpr uint32_t MODULE = 4294967161;
    uint32_t row, coloumn, value;
    std::map<std::pair<uint32_t, uint32_t>, uint32_t> matrix1;              //<<row, col>, val>
    while(std::cin >> row >> coloumn >> value && value != MODULE) {
        matrix1[{row, coloumn}] = value;
    }

    std::map<uint32_t, std::map<uint32_t, uint32_t>> matrix2;               //<row, <col, val>>
    while(std::cin >> row >> coloumn >> value) {
        matrix2[row][coloumn] = value;
    }

    std::map<std::pair<uint32_t, uint32_t>, uint32_t> result;               //<<row, col>, val>
    for(auto &[pos, value1] : matrix1) {
        uint32_t row = pos.first;
        uint32_t col = pos.second;
        auto row2 = col;
        for(auto &[col2, value2] : matrix2[row2]) {
            auto prod = (uint64_t(value1) * uint64_t(value2)) % MODULE;
            auto pos = std::make_pair(row, col2);
            result[pos] = (result[pos] + prod) % MODULE;
        }
    }

    print_matrix(result);
    return 0;
}
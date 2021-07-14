#include <iostream>
#include <string>
#include <iomanip>

int main() {
    std::ios_base::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout << std::hex;
    char c, prev = '\0';
    int counter = 1;
    if(!(std::cin.get(prev))){
        return 0;
    }
    while (std::cin.get(c)) {
        if (prev == c) {
            counter++;
        } else {
            if (counter <= 4 && prev != '#') {
                for (int i = 0; i < counter; i++) {
                    std::cout << prev;
                }
            } else {
                std::cout << '#' << prev << counter << '#';
            }
            counter = 1;
        }
        prev = c;
    }
    if (counter <= 4 && prev != '#') {
        for (int i = 0; i < counter; i++) {
            std::cout << prev;
        }
    } else {
        std::cout << '#' << prev << counter << '#';
    }

    return 0;
}
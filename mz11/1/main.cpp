#include <iostream>
#include <stack>
#include <string>

bool isop(char ch) {
    return ch == '+' || ch == '-' || ch == '*' || ch == '/';
}

int main() {
    char ch;
    std::stack<std::string> operands;
    while(std::cin >> ch) {
        if(isop(ch)) {
            std::string opd1 = operands.top();
            operands.pop();
            std::string opd2 = operands.top();
            operands.pop();
            operands.push("(" + opd2 + std::string(1, ch) + opd1 + ")");
        } else {
            operands.push(std::string(1, ch));
        }
    }
    std::cout << operands.top() << std::endl;
}
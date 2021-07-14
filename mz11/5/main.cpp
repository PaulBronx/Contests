#include <iostream>
#include <stack>

int main() {
    std::stack <std::string> stak;
    char c;
    while (std::cin >> c) {
        std::string a, b, res;
        switch (c) {
            case '+':
                a = stak.top();
                stak.pop();
                b = stak.top();
                stak.pop();
                res = "(" + b + "+" + a + ")";
                break;
            case '-':
                a = stak.top();
                stak.pop();
                b = stak.top();
                stak.pop();
                res = "(" + b + "-" + a + ")";
                break;
            case '*':
                a = stak.top();
                stak.pop();
                b = stak.top();
                stak.pop();
                res = "(" + b + "*" + a + ")";
                break;
            case '/':
                a = stak.top();
                stak.pop();
                b = stak.top();
                stak.pop();
                res = "(" + b + "/" + a + ")";
                break;
            default:
                res = c;
                break;
        }
        stak.push(res);
    }
    std::cout << stak.top() << std::endl;
}
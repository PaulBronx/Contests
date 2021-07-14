#include <iostream>
#include <string>

int main()
{
    std::string str;
    while (std::cin >> str)
    {
        char stat = '0', prev;
        int flag = 1 ;
        size_t iter = 0;
        while (iter < str.size())
        {
            prev = stat;
            if (str[iter] == '3' || str[iter] == '4') {
                stat = '0';
            } else if (str[iter] == '1' || str[iter] == '2') {
                stat = '1';
            } else {
                flag = 0;
                break;
            }
            if (prev == '1' && stat == '0') {
                flag = 0;
                break;
            }
            ++iter;
        }
        std::cout << flag << '\n';
    }
    return 0;
}
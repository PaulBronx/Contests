#include <iostream>
#include <string>

std::string gen_power(uint32_t power)
{
    std::string str;
    if (!power) {
        str = "1";
    } else if (power == 1){
        str = "x";
    } else {
        if (power % 2 == 0) {
            str = gen_power(power / 2);
            str += str;
            str += '*';
        } else {
            str = gen_power(power - 1);
            str += "x*";
        }
    }

    return str;
}

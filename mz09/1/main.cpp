#include <iostream>
#include <string>

class Printer
{
    std::string data_;
public:
    Printer()
    {
        if (!(std::cin >> data_))
        {
            throw 1;
        }
    }

    ~Printer()
    {
        std::cout << data_ << std::endl;
    }
};

void rev()
{
    Printer r;
    try {
        rev();
    } catch(...) {
        throw;
    }
}

int main()
{
    try {
        rev();
    } catch(...) {}
}
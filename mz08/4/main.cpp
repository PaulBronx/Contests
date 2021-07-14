#include <iostream>

class String
{
    struct Buf;
public:
    size_t size()
    {

    }
};

struct String::Buf
{
    bool unique = true;
    char *buf{};
    size_t size{};

    explicit Buf(char *str)
    {
        char *ptr = str;
        for (int i = 0; str[i] != )
        {
            buf[i] = ptr[i];
        }
    }
};

int main()
{
    String c, a = "abc";
    String b = a;
    c = a;
    b += "aaa";
    c[1] = 'f';
    std::cout << String(c);
}
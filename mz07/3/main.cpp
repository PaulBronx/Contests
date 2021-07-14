#include <iostream>
#include <sstream>
#include <vector>
#include <map>
#include <algorithm>
#include <functional>
#include <memory>

class Factory
{
    const std::map<char, std::function<Figure* (const std::string&)>> figures = {
            {'R', Rectangle::make},
            {'S', Square::make},
            {'C', Circle::make}
    };

public:
    std::shared_ptr<Figure> make(std::string str) const
    {
        char type;
        std::string params;

        std::istringstream input{str};
        input >> type;
        std::getline(input, params);

        return std::shared_ptr<Figure>(figures.find(type)->second(params));
    }
};

static Factory factory_instance()
{
    static Factory f;
    return f;
}

int main()
{
    std::vector<std::shared_ptr<Figure>> figures;

    std::string input;
    while(std::getline(std::cin, input))
    {
        figures.emplace_back(std::move(factory_instance().make(input)));
    }

    std::stable_sort(figures.begin(), figures.end(),
                     [](const std::unique_ptr<Figure>& f1, const std::unique_ptr<Figure>& f2)
                     {
                         return f1->get_square() < f2->get_square();
                     });

    for (size_t i = 0; i < figures.size(); ++i)
    {
        std::cout << figures[i]->to_string() << std::endl;
    }
}
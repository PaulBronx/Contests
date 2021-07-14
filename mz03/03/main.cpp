#include <string>
#include <vector>
#include <map>
#include <functional>

namespace numbers {
    complex eval(const std::vector<std::string> &args, const complex &z) {
        complex_stack stack_;
        std::map<char, std::function<complex_stack(complex_stack, complex)>> oper =
                {
                        {'z', [](complex_stack stack_, complex z) {
                            return stack_ << z;
                        }},
                        {'+', [](complex_stack stack_, complex z) {
                            return (~~stack_) << ((+~stack_) + (+stack_));
                        }},
                        {'-', [](complex_stack stack_, complex z) {
                            return (~~stack_) << ((+~stack_) - (+stack_));
                        }},
                        {'*', [](complex_stack stack_, complex z) {
                            return (~~stack_) << ((+~stack_) * (+stack_));
                        }},
                        {'/', [](complex_stack stack_, complex z) {
                            return (~~stack_) << ((+~stack_) / (+stack_));
                        }},
                        {'!', [](complex_stack stack_, complex z) {
                            return stack_ << +stack_;
                        }},
                        {';', [](complex_stack stack_, complex z) {
                            return ~stack_;
                        }},
                        {'~', [](complex_stack stack_, complex z) {
                            return ~stack_ << ~+stack_;
                        }},
                        {'#', [](complex_stack stack_, complex z) {
                            return ~stack_ << - +stack_;
                        }}
                };
        for (auto i : args) {
            if (i[0] == '(') {
                stack_ = stack_ << complex(i);
            } else {
                stack_ = oper[i[0]](stack_, z);
            }
        }
        return +stack_;
    }
}
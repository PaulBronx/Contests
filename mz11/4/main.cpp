#include <iostream>
#include <vector>

namespace Grammar {
    bool IsNonterm(char c) {
        return c >= 'A' && c <= 'Z';
    }

    bool IsTerm(char c) {
        return (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9');
    }

    bool contain_S(const std::string &s) {
        for (auto x: s) {
            if (x == 'S') {
                return true;
            }
        }
        return false;
    }

    int check_single_nonterm(std::string &s) {
        int n = 0;
        for (auto x: s) {
            n += (x >= 'A' && x <= 'Z');
        }
        return n;
    }

    bool check_left(std::vector<std::pair<char, std::string>> &data) {
        for (auto &[c, s]: data) {
            int n_NT = check_single_nonterm(s);
            if (n_NT > 1) {
                return false;
            }
            if (n_NT == 1 && !IsNonterm(s.front())) {
                return false;
            }
        }
        return true;
    }

    bool check_auto_left(std::vector<std::pair<char, std::string>> &data) {
        bool is_eps{}, is_nont{};
        int num_single_nont = 0;
        bool S_in_right = false;
        for (auto &[c, s]: data) {
            if (s.length() > 2) {
                return false;
            }
            if (s == "_") {
                if (c != 'S') {
                    return false;
                }
                is_eps = true;
            }
            if (s.length() == 1 && IsNonterm(s.front())) {
                if (c != 'S' || num_single_nont) {
                    return false;
                }
                is_nont = true;
                num_single_nont++;
            }
            if (s.length() == 2 && !(IsNonterm(s[0]) && IsTerm(s[1]))) {
                return false;
            }
            if (contain_S(s)) {
                S_in_right = true;
            }
        }
        if (!is_eps && !is_nont) {
            return true;
        }
        return !S_in_right;
    }

    bool check_right(std::vector<std::pair<char, std::string>> &data) {
        for (auto &[c, s]: data) {
            int n_NT = check_single_nonterm(s);
            if (n_NT > 1) {
                return false;
            }
            if (n_NT == 1 && !IsNonterm(s.back())) {
                return false;
            }
        }
        return true;
    }

    bool check_auto_right(std::vector<std::pair<char, std::string>> &data) {
        bool is_eps{}, is_nont{};
        int num_single_nont = 0;
        bool S_in_right = false;
        for (auto &[c, s]: data) {
            if (s.length() > 2) {
                return false;
            }
            if (s == "_") {
                if (c != 'S') {
                    return false;
                }
                is_eps = true;
            }
            if (s.length() == 1 && IsNonterm(s.front())) {
                if (c != 'S' || num_single_nont) {
                    return false;
                }
                is_nont = true;
                num_single_nont++;
            }
            if (s.length() == 2 && !(IsNonterm(s[1]) && IsTerm(s[0]))) {
                return false;
            }
            if (contain_S(s)) {
                S_in_right = true;
            }
        }
        if (!is_eps && !is_nont) {
            return true;
        }
        return !S_in_right;
    }

    bool check_nonshort(std::vector<std::pair<char, std::string>> &data) {
        bool is_eps = false, S_in_right = false;
        for (auto &[c, s]: data) {
            if (s == "_") {
                if (c != 'S') {
                    return false;
                }
                is_eps = true;
            }
            if (contain_S(s)) {
                S_in_right = true;
            }
        }
        if (!is_eps) {
            return true;
        }
        return !S_in_right;
    }
}


int main() {
    std::vector<std::pair<char, std::string>> data;
    char left;
    std::string right;
    while (std::cin >> left >> right) {
        data.emplace_back(std::make_pair(left, right));
    }
    if (Grammar::check_left(data)) {
        if (Grammar::check_auto_left(data)) {
            std::cout << 311 << std::endl;
        } else {
            std::cout << 31 << std::endl;
        }
        return 0;
    }
    if (Grammar::check_right(data)) {
        if (Grammar::check_auto_right(data)) {
            std::cout << 321 << std::endl;
        } else {
            std::cout << 32 << std::endl;
        }
        return 0;
    }
    if (Grammar::check_nonshort(data)) {
        std::cout << 21 << std::endl;
    } else {
        std::cout << 2 << std::endl;
    }
    return 0;
}
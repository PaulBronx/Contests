#include <iostream>
#include <set>
#include <vector>
#include <string>
#include <cctype>
#include <map>

int main() {
    char c;
    std::string s;
    std::multimap<char, std::string> mapa;
    while(std::cin >> c >> s) {
        mapa.insert({c, s});
    }
    std::set<char> used;
    std::vector<char> cur;
    used.insert('S');
    cur.push_back('S');
    for(size_t i = 0; i < cur.size(); ++i) {
        auto x = mapa.equal_range(cur[i]);
        for (; x.first != x.second; ++x.first) {
            for(auto ch : x.first->second) {
                if(isupper(ch)) {
                    if(used.insert(ch).second) {
                        cur.push_back(ch);
                    }
                }
            }
        }
    }
    for(auto &w : mapa) {
        if(used.find(w.first) != used.end()) {
            std::cout << w.first << " " << w.second << std::endl;
        }
    }
}

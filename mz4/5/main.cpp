#include <iostream>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <string>
#include <set>
#include <vector>
#include <algorithm>

struct Cell {
    Cell(int p_x = 0, int p_y = 0, int h = 0) : x(p_x), y(p_y), height(h) {}

    int x;
    int y;
    int height;
};

struct cmp {
    bool operator()(Cell c1, Cell c2) const {
        if (c1.height == c2.height) {
            if (c1.y == c2.y) {
                return c1.x > c2.x;
            }
            return c1.y > c2.y;
        }
        return c1.height < c2.height;
    }
};

int get_field(std::ifstream &in, std::vector <std::vector<int>> &field) {
    std::string str;
    int i;
    for (i = 0; std::getline(in, str); i++) {
        std::stringstream line(str);
        std::vector<int> row;
        int tmp;
        while (line >> tmp) {
            row.push_back(tmp);
        }
        if (row.size()) {
            field.push_back(row);
        } else {
            break;
        }
    }
    return i;
}

void del_field(std::vector <std::vector<int>> &field) {
    return;
}

void make_cells(const std::vector <std::vector<int>> &field, std::set <Cell, cmp> &cells) {
    for (unsigned i = 0; i < field.size(); ++i) {
        for (unsigned j = 0; j < field[i].size(); ++j) {
            cells.insert(Cell(j, i, field[i][j]));
        }
    }
}

int get_changes(std::ifstream &in, std::vector<int> &changes) {
    int tmp;
    while (in >> tmp) {
        changes.push_back(tmp);
    }
    return changes.size();
}

bool on_map(const int x, const int y, const std::vector <std::vector<int>> &field) {
    return 0 <= y && unsigned(y) < field.size() && 0 <= x && unsigned(x) < field[y].size();
}
/*
void print_cells(const std::set <Cell, cmp> cells) {
    for (auto cell : cells) {
        std::cout << "[" << cell.y << "," << cell.x << "]:" << cell.height << std::endl;
    }
}
*/
void change(int &height, const int change) {
    if (height > 0) {
        height -= change;
    }
}

void accept_change(std::vector <std::vector<int>> &field, int ch) {
    std::set <Cell, cmp> cells;
    make_cells(field, cells);
    static struct {
        int dy, dx, k;
    } d[8] = {
            {-1, 0,  2},
            {0,  +1, 2},
            {+1, 0,  2},
            {0,  -1, 2},
            {-1, -1, 4},
            {+1, -1, 4},
            {-1, +1, 4},
            {+1, +1, 4}
    };

    auto cell = cells.rbegin();
    int y = cell->y;
    int x = cell->x;

    change(field[y][x], ch);

    for (int i = 0; i < 8; ++i) {
        if (on_map(x + d[i].dx, y + d[i].dy, field)) {
            change(field[y + d[i].dy][x + d[i].dx], ch / +d[i].k);
        }
    }
}

void print_field(const std::vector <std::vector<int>> &field) {
    for (auto items : field) {
        for (auto item : items) {
            if (item < 0) {
                item = 0;
            }
            std::cout << std::right << std::setw(2) << item << " ";
        }
        std::cout << std::endl;
    }
}

int main() {
    std::ifstream in("test1.txt");
    std::vector <std::vector<int>> field;
    if (get_field(in, field)) {
        print_field(field);
        std::vector<int> changes;
        if (get_changes(in, changes)) {
            std::sort(changes.begin(), changes.end());
            for (auto ch_it = changes.rbegin(); ch_it < changes.rend(); ++ch_it) {
                int change = *ch_it;
                accept_change(field, change);
                print_field(field);
            }
        }
        print_field(field);
        del_field(field);
    }
}


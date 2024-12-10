#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cassert>
#include <unordered_set>
#include <stack>

int main(int argc,  char** argv) {
    assert(argc == 2);
    std::ifstream file;
    file.open(argv[1], std::ios_base::in);

    std::vector<std::vector<char>> map;
    std::stack<std::pair<int,int>> start_nodes;
    std::string line;
    int y = 0;
    int width, height;
    while (std::getline(file, line)) {
        if (y == 0) width = line.size();
        auto ss = std::stringstream(line);
        char c;
        int x = 0;
        std::vector<char> row;
        while (ss >> c) {
            if (c == '0') start_nodes.push({x, y});
            row.push_back(c - '0');
            x++;
        }
        map.push_back(row);
        y++;
    }
    height = y;

    int result = 0;
    auto hash = [width](int x, int y) { return x + width * y; };
    while (!start_nodes.empty()) {
        std::stack<std::pair<int,int>> nodes;
        nodes.push(start_nodes.top()); start_nodes.pop();

        std::unordered_set<int> seen;
        while (!nodes.empty()) {
            auto [x, y] = nodes.top(); nodes.pop();
            if (map[y][x] == 9) { result++; continue; }

            for (int i = 0; i < 4; i++) {
                // 00 ->  0  1
                // 01 ->  1  0
                // 10 ->  0 -1
                // 11 -> -1  0
                int dir = (i & 2) ? -1 : 1;
                int dx = (i & 1)  * dir;
                int dy = !(i & 1) * dir;
                if (x + dx < 0 || x + dx >= width || y + dy < 0 || y + dy >= height) continue;
                if (map[y + dy][x + dx] == map[y][x] + 1) {
                    if (seen.find(hash(x + dx, y + dy)) != seen.end()) continue;
                    nodes.push({x + dx, y + dy});
                    seen.insert(hash(x + dx, y + dy));
                }
            }
        }
    }

    std::cout << "Result " << result << std::endl;
}

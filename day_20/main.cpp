#include <iostream>
#include <fstream>
#include <sstream>
#include <cassert>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <stack>
#include <string.h>

struct pos_t { int x; int y; };
bool operator==(const pos_t& lhs, const pos_t& rhs) { return lhs.x == rhs.x && lhs.y == rhs.y; }
bool operator!=(const pos_t& lhs, const pos_t& rhs) { return !(lhs == rhs); }
std::ostream &operator << (std::ostream & outs, const pos_t& pos) { return outs << "(" << pos.x << ", " << pos.y << ")"; }

int main(int argc,  char** argv) {
    assert(argc == 2);
    std::ifstream file(argv[1]);

    pos_t start, end;
    std::vector<std::string> input;
    for (std::string line; std::getline(file, line);) {
        if (int x = line.find("S"); x != -1) start = {x, (int)input.size()};
        if (int x = line.find("E"); x != -1) end = {x, (int)input.size()};
        input.push_back(line);
    }

    std::vector<pos_t> path;
    int index = 0;
    pos_t pos = start;
    path.push_back(pos);
    while (pos != end) {
        for (auto p : std::vector<pos_t>{{pos.x-1, pos.y}, {pos.x+1, pos.y}, {pos.x, pos.y-1}, {pos.x, pos.y+1}}) {
            if (input[p.y][p.x] != '#' && (path.size() < 2 || path[path.size()-2] != p)) {
                path.push_back(p);
                pos = p;
                break;
            }
        }
    }

    int part_1 = 0;
    int part_2 = 0;
    for (int i = 0; i < path.size(); i++) {
        auto pos0 = path[i];
        for (int j = i+3; j < path.size(); j++) {
            auto pos1 = path[j];
            if (int dist = abs(path[i].x - path[j].x) + abs(path[i].y - path[j].y); dist <= 20) {
                int gain = (j - i) - dist;
                if (gain >= 100) part_2++;
                if (gain >= 100 && dist == 2) part_1++;
            }
        }
    }

    std::cout << "Result (part 1): " << part_1 << std::endl;
    std::cout << "Result (part 2): " << part_2 << std::endl;
}

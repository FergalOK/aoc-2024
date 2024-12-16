#include <iostream>
#include <fstream>
#include <cassert>
#include <vector>
#include <queue>
#include <unordered_set>

struct pos {
    int x;
    int y;
    int dir;
};

int main(int argc,  char** argv) {
    assert(argc == 2);
    std::ifstream file(argv[1]);

    pos start, end;
    std::vector<std::vector<char>> map;
    for (std::string line; std::getline(file, line);) {
        std::vector<char> row;
        for (char c : line) {
            if (c == 'S') start = {(int)row.size(), (int)map.size()};
            if (c == 'E') end = {(int)row.size(), (int)map.size()};
            row.push_back(c);
        }
        map.push_back(row);
    }

    int width = map[0].size();
    auto hash = [width](std::pair<int,int> position) { return position.first + width * position.second; };
    std::unordered_set<std::pair<int,int>, decltype(hash)> seen(10, hash);

    auto cmp = [](std::pair<int,pos> left, std::pair<int,pos> right) {return left.first > right.first; };
    std::priority_queue<std::pair<int,pos>,std::vector<std::pair<int,pos>>, decltype(cmp)> heap(cmp);
    heap.push({0, start});
    seen.insert({start.x, start.y});
    while (!heap.empty()) {
        auto [c, p] = heap.top(); heap.pop();
        for (int dir = 0; dir < 4; dir++) {
            int cost = c;
            int dx = !(dir & 1) * (1 - (dir & 2));
            int dy = (dir & 1) * (1 - (dir & 2));

            if (map[p.y+dy][p.x+dx] == '#') continue;
            if (seen.find({p.x+dx, p.y+dy}) != seen.end()) continue;

            if ((p.dir ^ dir) == 2) cost += 2000;
            else if (p.dir != dir) cost += 1000;

            heap.push({cost+1, {p.x+dx, p.y+dy, dir}});
            seen.insert({p.x+dx, p.y+dy});
            if (p.x+dx == end.x && p.y+dy == end.y) {
                std::cout << "Result: " << cost+1 << std::endl;
                exit(0);
            }
        }
    }


}

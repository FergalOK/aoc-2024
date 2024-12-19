#include <iostream>
#include <fstream>
#include <cassert>
#include <vector>
#include <queue>
#include <stack>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>

struct pos {
    int x;
    int y;
    int dir;
};

bool operator==(const pos& lhs, const pos& rhs) {
    return lhs.x == rhs.x && lhs.y == rhs.y && lhs.dir == rhs.dir;
}

int main(int argc,  char** argv) {
    assert(argc == 2);
    std::ifstream file(argv[1]);

    pos start;
    std::pair<int,int> end;
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
    auto hash = [width](pos position) { return position.dir + 4 * (position.x + width * position.y); };
    std::unordered_map<pos, int, decltype(hash)> seen(10, hash);
    std::unordered_multimap<pos, pos, decltype(hash)> graph(10, hash);

    auto cmp = [](std::pair<int,pos> left, std::pair<int,pos> right) {return left.first > right.first; };
    std::priority_queue<std::pair<int,pos>,std::vector<std::pair<int,pos>>, decltype(cmp)> heap(cmp);
    heap.push({0, start});
    seen.insert({{{start.x, start.y}, 0}});
    while (!heap.empty()) {
        auto [c, p] = heap.top(); heap.pop();
        int dx = std::vector<int>{1, 0, -1, 0}[p.dir];
        int dy = std::vector<int>{0, 1, 0, -1}[p.dir];
        pos clockwise = {p.x, p.y, (p.dir+1) % 4};
        pos counterclock = {p.x, p.y, (p.dir+3) % 4};
        pos forward = {p.x + dx, p.y + dy, p.dir};
        if (seen.find(clockwise) == seen.end()) {
            heap.push({c+1000, clockwise});
            seen.insert({clockwise, c+1000});
            graph.insert({clockwise, p});
        }
        else if (c+1000 <= seen[clockwise]) graph.insert({clockwise, p});

        if (seen.find(counterclock) == seen.end()) {
            heap.push({c+1000, counterclock});
            seen.insert({counterclock, c+1000});
            graph.insert({counterclock, p});
        }
        else if (c+1000 <= seen[counterclock]) graph.insert({counterclock, p});

        if (seen.find(forward) == seen.end()) {
            if (map[forward.y][forward.x] != '#') {
                heap.push({c+1, forward});
                seen.insert({forward, c+1});
                graph.insert({forward, p});
            }
        }
        else if (c+1 <= seen[forward]) graph.insert({forward, p});
    }

    std::vector<pos> ends {{end.first, end.second, 0}, {end.first, end.second, 1}, {end.first, end.second, 2}, {end.first, end.second, 3}};
    int part_1 = seen[ends[0]];
    for (int i = 1; i < ends.size(); i++) part_1 = std::min(part_1, seen[ends[i]]);
    std::cout << "Result (part 1): " << part_1 << std::endl;

    // Part 2
    auto pair_hash = [width](std::pair<int,int> position) { return position.first + width * position.second; };
    std::unordered_set<std::pair<int,int>, decltype(pair_hash)> unique_pos(10, pair_hash);
    std::stack<pos> unvisited;
    for (auto e : ends) unvisited.push(e);

    while (!unvisited.empty()) {
        pos position = unvisited.top(); unvisited.pop();
        auto range = graph.equal_range(position);
        for (auto it = range.first; it != range.second; it++) {
            unvisited.push(it->second);
            unique_pos.insert({it->second.x, it->second.y});
        }
    }

    std::cout << "Result (part 2): " << unique_pos.size() << std::endl;
}

#include <iostream>
#include <fstream>
#include <sstream>
#include <cassert>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <string.h>

int width = 71;
int height = 71;

int solve(std::vector<std::pair<int,int>> falling, int nfall) {
    auto hash = [](std::pair<int,int> pos){ return pos.first + width * pos.second; };
    std::unordered_set<std::pair<int,int>, decltype(hash)> seen(10, hash);
    std::vector<std::pair<int,int>> positions;
    seen.insert({0, 0});
    positions.push_back({0, 0});
    for (int i = 0; i < nfall; i++) seen.insert(falling[i]);

    int nsteps = 0;
    while (!positions.empty()) {
        nsteps++;
        std::vector<std::pair<int,int>> next;
        for (auto p : positions) {
            for (std::pair<int,int> adj : std::vector<std::pair<int,int>>{{p.first-1, p.second}, {p.first+1, p.second}, {p.first, p.second-1}, {p.first, p.second+1}}) {
                if (adj.first < 0 || adj.first >= width || adj.second < 0 || adj.second >= height) continue;
                if (adj == std::pair<int,int>{width-1, height-1}) return nsteps;
                if (seen.find(adj) == seen.end()) {
                    next.push_back(adj);
                    seen.insert(adj);
                }
            }
        }
        positions = next;
    }

    return -1;
}

int main(int argc,  char** argv) {
    assert(argc == 2);
    std::ifstream file(argv[1]);

    int nfall = 1024;
    if (strcmp(argv[1], "example.txt") == 0) {
        width = 7;
        height = 7;
        nfall = 12;
    }

    std::vector<std::pair<int,int>> falling;
    for (std::string line; std::getline(file, line);) {
        std::stringstream ss(line);
        std::pair<int,int> pos;
        char c;
        ss >> pos.first >> c >> pos.second;
        assert(c == ',');
        falling.push_back(pos);
    }

    int steps = solve(falling, nfall);
    std::cout << "Result (part 1): " << steps << std::endl;

    int left = nfall;
    int right = falling.size()-1;
    while (left < right) {
        int pivot = left + (right - left) / 2;
        steps = solve(falling, pivot);
        if (steps != -1) left = pivot + 1;
        else right = pivot;
    }
    std::pair<int,int> result = falling[right-1];
    std::cout << "Result (part 2): " << result.first << "," << result.second << std::endl;
}

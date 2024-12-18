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
int nfall = 1024;

int part_1(std::vector<std::pair<int,int>> falling) {
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

    std::cout << "Result (part 1): " << part_1(falling) << std::endl;
}

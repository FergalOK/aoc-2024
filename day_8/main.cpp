#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cassert>
#include <unordered_map>
#include <unordered_set>

int main(int argc,  char** argv) {
    assert(argc == 2);
    std::ifstream file;
    file.open(argv[1], std::ios_base::in);

    std::unordered_map<char, std::vector<std::pair<int,int>>> a;
    std::string line;
    int y = 0;
    while (std::getline(file, line)) {
        for (size_t x = 0; x < line.size(); x++) {
            if (line[x] == '.') continue;
            if (a.find(line[x]) == a.end()) a[line[x]] = std::vector<std::pair<int,int>>();
            a[line[x]].push_back({x, y});
        }
        y++;
    }

    size_t height = y;
    size_t width = line.size();
    auto hash = [width](int x, int y) { return x + width * y; };
    std::unordered_set<int> antinodes;
    for (auto freq : a) {
        std::vector<std::pair<int,int>> positions = freq.second;
        for (size_t i = 0; i < positions.size(); i++) {
            for (size_t j = 0; j < positions.size(); j++) {
                if (i == j) {
                    antinodes.insert(hash(positions[i].first, positions[i].second));
                    continue;
                }
                int dx = positions[i].first - positions[j].first;
                int dy = positions[i].second - positions[j].second;
                int x = positions[i].first + dx;
                int y = positions[i].second + dy;
                while (x >= 0 && x < width && y >= 0 && y < height) {
                    antinodes.insert(hash(x, y));
                    x += dx;
                    y += dy;
                }
            }
        }
    }

    std::cout << "Result " << antinodes.size() << std::endl;
}

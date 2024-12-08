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
            for (size_t j = i+1; j < positions.size(); j++) {
                int x0 = 2 * positions[i].first - positions[j].first;
                int y0 = 2 * positions[i].second - positions[j].second;
                if (x0 >= 0 && x0 < width && y0 >= 0 && y0 < height) antinodes.insert(hash(x0, y0));

                int x1 = 2 * positions[j].first - positions[i].first;
                int y1 = 2 * positions[j].second - positions[i].second;
                if (x1 >= 0 && x1 < width && y1 >= 0 && y1 < height) antinodes.insert(hash(x1, y1));
            }
        }
    }

    std::cout << "Result " << antinodes.size() << std::endl;
}

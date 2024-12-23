#include <iostream>
#include <fstream>
#include <sstream>
#include <cassert>
#include <unordered_set>
#include <unordered_map>
#include <vector>

std::vector<std::string> input;
std::unordered_set<int> seen;
std::unordered_map<int, int> sides;

struct params {
    int perim;
    int area;
    int sides;
};

params calculate(int x, int y) {
    params result {};
    int width = input[0].size();
    auto hash = [width](int x, int y) { return x + width * y; };
    if (sides.find(hash(x, y)) != sides.end()) result.sides = sides[hash(x, y)];

    if (seen.find(hash(x, y)) != seen.end()) return {};
    else seen.insert(hash(x, y));

    result.area = 1;
    for (int i = 0; i < 4; i++) {
        int dx = (i & 1) * ((i & 2) - 1);
        int dy = !(i & 1) * ((i & 2) - 1);

        bool x_border = x + dx < 0 || x + dx >= input.size();
        bool y_border = y + dy < 0 || y + dy >= input[0].size();
        if (x_border || y_border || input[x][y] != input[x+dx][y+dy]) {
            result.perim++;
            continue;
        }

        params sub_result = calculate(x + dx, y + dy);
        result.perim += sub_result.perim;
        result.area += sub_result.area;
        result.sides += sub_result.sides;
    }

    return result;
}


int main(int argc,  char** argv) {
    assert(argc == 2);
    std::ifstream file;
    file.open(argv[1], std::ios_base::in);

    std::string line;
    while (std::getline(file, line)) input.push_back(line);

    int width = input[0].size();
    auto hash = [width](int x, int y) { return x + width * y; };
    for (int i = 0; i < input.size(); i++) {
        for (int j = 0; j < width; j++) {
            char val = input[i][j];
            for (int k = 0; k < 4; k++) {
                int dx = 2 * (k & 1) - 1;
                int dy = (k & 2) - 1;
                bool x_range = i+dx < 0 || i+dx >= input.size();
                bool y_range = j+dy < 0 || j+dy >= width;
                bool parallel = x_range || y_range || val != input[i+dx][j+dy];
                bool x_axe = x_range || val != input[i+dx][j];
                bool y_axe = y_range || val != input[i][j+dy];
                if ((parallel && (x_axe == y_axe)) || (x_axe && y_axe)) {
                    int h = hash(i, j);
                    if (sides.find(h) == sides.end()) sides.insert({h, 0});
                    sides[h]++;
                }
            }
        }
    }

    int result_part1 = 0;
    int result_part2 = 0;
    for (int i = 0; i < input.size(); i++) {
        for (int j = 0; j < width; j++) {
            if (seen.find(hash(i, j)) != seen.end()) continue;
            params val = calculate(i, j);
            result_part1 += val.area * val.perim;
            result_part2 += val.area * val.sides;
        }
    }

    std::cout << "Result (part 1): " << result_part1 << std::endl;
    std::cout << "Result (part 2): " << result_part2 << std::endl;
}

#include <iostream>
#include <fstream>
#include <sstream>
#include <cassert>
#include <unordered_set>
#include <vector>

std::vector<std::string> input;
std::unordered_set<int> seen;
int hash(int x, int y);

struct params {
    int perim;
    int area;
};

params calculate(int x, int y) {
    int width = input[0].size();
    auto hash = [width](int x, int y) { return x + width * y; };
    if (seen.find(hash(x, y)) != seen.end()) return {};
    else seen.insert(hash(x, y));

    params result {0, 1};
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
    }

    return result;
}

int main(int argc,  char** argv) {
    assert(argc == 2);
    std::ifstream file;
    file.open(argv[1], std::ios_base::in);

    std::string line;
    while (std::getline(file, line)) {
        input.push_back(line);
    }

    int width = input[0].size();
    int result = 0;
    for (int i = 0; i < input.size(); i++) {
        for (int j = 0; j < width; j++) {
            params val = calculate(i, j);
            result += val.area * val.perim;
        }
    }

    std::cout << "Result (part 1): " << result << std::endl;
}

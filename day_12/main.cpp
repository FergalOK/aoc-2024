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

#include <unordered_map>

int main(int argc,  char** argv) {
    assert(argc == 2);
    std::ifstream file;
    file.open(argv[1], std::ios_base::in);

    std::string line;
    while (std::getline(file, line)) {
        input.push_back(line);
    }


    int width = input[0].size();
    auto hash = [width](int x, int y) { return x + width * y; };
    std::unordered_map<int, int> sides;
    char prev = input[0][0];
    for (int j = 1; j < width; j++) {
        if (input[0][j] != prev) {
            int h = hash(0, j-1);
            if (sides.find(h) == sides.end()) sides.insert({h, 0});
            sides[h]++;
            std::cout << "Added " << 0 << ", " << j-1 << " " << prev << std::endl;
            prev = input[0][j];
        }
    }
    sides.insert({hash(0, width-1), 1});
    std::cout << "Added " << 0 << ", " << width-1 << " " << prev << std::endl;
    std::cout << "BREAK"<<std::endl;
    for (int i = 1; i < input.size(); i++) {
        prev = input[i][0];
        bool side = false;
        for (int j = 1; j < width; j++) {            
            if (input[i][j] != prev || input[i-1][j] == prev) {
                if (side) {
                    int h = hash(i, j-1);
                    if (sides.find(h) == sides.end()) sides.insert({h, 0});
                    sides[h]++;
                    std::cout << "Added " << i << ", " << j-1 << " " << prev << std::endl;
                }
                prev = input[i][j];
                side =false;
            }
            if (input[i-1][j] != input[i][j]) side = true;
        }
    }

    // int result = 0;
    // for (int i = 0; i < input.size(); i++) {
    //     for (int j = 0; j < width; j++) {
    //         params val = calculate(i, j);
    //         result += val.area * val.perim;
    //     }
    // }

    // std::cout << "Result (part 1): " << result << std::endl;
}

#include <iostream>
#include <fstream>
#include <cassert>
#include <regex>

int main(int argc,  char** argv) {
    assert(argc == 2);
    std::ifstream file(argv[1]);
    int width = 101;
    int height = 103;
    if (strcmp(argv[1], "example.txt") == 0) {
        width = 11;
        height = 7;
    }

    int quadrants[4] {};
    for (std::string line; std::getline(file, line);) {
        std::regex re("p=(.+),(.+) v=(.+),(.+)");
        std::smatch match;
        std::regex_search(line, match, re);

        int x = stoi(match[1]);
        int y = stoi(match[2]);
        int vx = stoi(match[3]);
        int vy = stoi(match[4]);
        int x_final = ((x + vx * 100) % width + width) % width;
        int y_final = ((y + vy * 100) % height + height) % height;

        if (x_final == width / 2 || y_final == height / 2) continue;
        int n = 0;
        if (x_final > width / 2) n += 1;
        if (y_final > height / 2) n += 2;
        quadrants[n]++;
    }

    int result = 1;
    for (int i = 0; i < 4; i++) { result *= quadrants[i]; }
    std::cout << "Result (part 1): " << result << std::endl;
}

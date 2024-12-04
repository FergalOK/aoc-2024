#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <queue>
#include <regex>
#include <numeric>
#include <cassert>


int part_1(std::vector<std::string> lines);
int part_2(std::vector<std::string> lines);

int main(int argc,  char** argv) {
    assert(argc == 2);
    std::ifstream file;
    file.open(argv[1], std::ios_base::in);
    std::string l;
    std::vector<std::string> lines;
    while (std::getline(file, l)) lines.push_back(l);

    std::cout << "Part 1: " << part_1(lines) << std::endl;
    std::cout << "Part 2: " << part_2(lines) << std::endl;
}

int part_1(std::vector<std::string> lines) {
    int found = 0;
    int rows = lines.size();
    int cols = lines[0].size();
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (lines[i][j] != 'X') continue;

            if (i + 3 < rows && lines[i+1][j] == 'M' && lines[i+2][j] == 'A' && lines[i+3][j] == 'S') found++;
            if (i - 3 >= 0    && lines[i-1][j] == 'M' && lines[i-2][j] == 'A' && lines[i-3][j] == 'S') found++;
            if (j + 3 <= cols && lines[i][j+1] == 'M' && lines[i][j+2] == 'A' && lines[i][j+3] == 'S') found++;
            if (j - 3 >= 0    && lines[i][j-1] == 'M' && lines[i][j-2] == 'A' && lines[i][j-3] == 'S') found++;
            if (i + 3 < rows && j + 3 <= cols && lines[i+1][j+1] == 'M' && lines[i+2][j+2] == 'A' && lines[i+3][j+3] == 'S') found++;
            if (i + 3 < rows && j - 3 >= 0    && lines[i+1][j-1] == 'M' && lines[i+2][j-2] == 'A' && lines[i+3][j-3] == 'S') found++;
            if (i - 3 >= 0    && j + 3 <= cols && lines[i-1][j+1] == 'M' && lines[i-2][j+2] == 'A' && lines[i-3][j+3] == 'S') found++;
            if (i - 3 >= 0    && j - 3 >= 0    && lines[i-1][j-1] == 'M' && lines[i-2][j-2] == 'A' && lines[i-3][j-3] == 'S') found++;
        }
    }

    return found;
}

int part_2(std::vector<std::string> lines) {
    int found = 0;
    int rows = lines.size();
    int cols = lines[0].size();
    for (int i = 1; i < rows-1; i++) {
        for (int j = 1; j < cols-1; j++) {
            if (lines[i][j] != 'A') continue;

            bool first = (lines[i-1][j-1] == 'M' && lines[i+1][j+1] == 'S')
                      || (lines[i-1][j-1] == 'S' && lines[i+1][j+1] == 'M');
            bool second = (lines[i-1][j+1] == 'M' && lines[i+1][j-1] == 'S')
                       || (lines[i-1][j+1] == 'S' && lines[i+1][j-1] == 'M');

            if (first && second) found++;
        }
    }

    return found;
}

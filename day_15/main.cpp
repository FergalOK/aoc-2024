#include <iostream>
#include <fstream>
#include <cassert>
#include <vector>


int main(int argc,  char** argv) {
    assert(argc == 2);
    std::ifstream file(argv[1]);

    std::pair<int,int> pos;
    std::vector<std::string> map;
    int y = 0;
    int width;
    for (std::string line; std::getline(file, line); y++) {
        if (y == 0) width = line.size();
        if (line == "") break;
        map.push_back(line);
        int x = line.find('@');
        if (x != -1) {
            pos = {x, y};
            map[pos.second][pos.first] = '.';
        }
    }
    int height = y;

    char movement;
    while (file >> movement) {
        if (movement == '\n') continue;
        if (movement == '>') {
            bool can_move = true;
            int x;
            for (x = pos.first+1; x < width; x++) {
                if (map[pos.second][x] == '.') break;
                else if (map[pos.second][x] == '#') { can_move = false; break; }
            }
            if (!can_move) continue;
            for (x; x > pos.first; x--) { map[pos.second][x] = map[pos.second][x-1]; }
            pos.first++;
        }
        else if (movement == '<') {
            bool can_move = true;
            int x;
            for (x = pos.first-1; x >= 0; x--) {
                if (map[pos.second][x] == '.') break;
                else if (map[pos.second][x] == '#') { can_move = false; break; }
            }
            if (!can_move) continue;
            for (x; x < pos.first; x++) { map[pos.second][x] = map[pos.second][x+1]; }
            pos.first--;
        }
        else if (movement == 'v') {
            bool can_move = true;
            int y;
            for (y = pos.second+1; y < height; y++) {
                if (map[y][pos.first] == '.') break;
                else if (map[y][pos.first] == '#') { can_move = false; break; }
            }
            if (!can_move) continue;
            for (y; y > pos.second; y--) { map[y][pos.first] = map[y-1][pos.first]; }
            pos.second++;
        }
        else if (movement == '^') {
            bool can_move = true;
            int y;
            for (y = pos.second-1; y >= 0; y--) {
                if (map[y][pos.first] == '.') break;
                else if (map[y][pos.first] == '#') { can_move = false; break; }
            }
            if (!can_move) continue;
            for (y; y < pos.second; y++) { map[y][pos.first] = map[y+1][pos.first]; }
            pos.second--;
        }
    }

    // Display final map
    for (std::string row : map) std::cout << row << std::endl;

    int result = 0;
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            if (map[y][x] == 'O') result += x + 100 * y;
        }
    }

    std::cout << "Result (part 1): " << result << std::endl;
}

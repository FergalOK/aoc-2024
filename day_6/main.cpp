#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cassert>
#include <unordered_map>
#include <unordered_set>

#define UP 0
#define RIGHT 1
#define DOWN 2
#define LEFT 3

int main(int argc,  char** argv) {
    assert(argc == 2);
    std::ifstream file;
    file.open(argv[1], std::ios_base::in);

    std::vector<std::string> map;
    int guard_x = -1, guard_y = -1;
    int guard_dir = UP;
    std::string line;
    while (std::getline(file, line)) {
        map.push_back(line);
        int x = line.find("^");
        if (x != -1) {
            guard_x = x;
            guard_y = map.size() - 1;
        }
    }
    assert(guard_x != -1 && guard_y != -1);

    size_t height = map.size();
    size_t width = map[0].size();
    auto hash_fn = [width](const std::pair<int,int> &v) { return v.first + width * v.second; };
    std::unordered_set<std::pair<int, int>, decltype(hash_fn)> seen(10, hash_fn);

    while (guard_x >= 0 && guard_x < width && guard_y >= 0 && guard_y < height) {
        std::cout << guard_x << ", " << guard_y << ", " << guard_dir << std::endl;
        seen.insert({guard_x, guard_y});
        if (guard_dir == UP) {
            if (guard_y == 0) break;
            if (map[guard_y-1][guard_x] == '#') guard_dir = RIGHT;
            else guard_y--;
        }
        else if (guard_dir == DOWN) {
            if (guard_y == height-1) break;
            if (map[guard_y+1][guard_x] == '#') guard_dir = LEFT;
            else guard_y++;
        }
        else if (guard_dir == RIGHT) {
            if (guard_x == width-1) break;
            if (map[guard_y][guard_x+1] == '#') guard_dir = DOWN;
            else guard_x++;
        }
        else if (guard_dir == LEFT) {
            if (guard_x == 0) break;
            if (map[guard_y][guard_x-1] == '#') guard_dir = UP;
            else guard_x--;
        }
    }
    
    std::cout << "Result " << seen.size() << std::endl;
}

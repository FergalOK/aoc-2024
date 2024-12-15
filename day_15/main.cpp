#include <iostream>
#include <fstream>
#include <cassert>
#include <vector>
#include <stack>
#include <unordered_set>

int solve(std::vector<std::vector<char>> map, std::pair<int,int> pos, std::vector<char> moves);

int main(int argc,  char** argv) {
    assert(argc == 2);
    std::ifstream file(argv[1]);

    std::pair<int,int> pos_part1;
    std::pair<int,int> pos_part2;
    std::vector<std::vector<char>> map_part1;
    std::vector<std::vector<char>> map_part2;
    int y = 0;
    for (std::string line; std::getline(file, line); y++) {
        if (line == "") break;
        std::vector<char> row_part1;
        std::vector<char> row_part2;
        for (size_t i = 0; i < line.size(); i++) {
            // Part 1
            if (line[i] == '@') {
                pos_part1 = {row_part1.size(), y};
                row_part1.push_back('.');
            }
            else { row_part1.push_back(line[i]); }

            // Part 2
            if (line[i] == '.') row_part2.insert(row_part2.end(), {'.', '.'});
            if (line[i] == '#') row_part2.insert(row_part2.end(), {'#', '#'});
            if (line[i] == 'O') row_part2.insert(row_part2.end(), {'[', ']'});
            if (line[i] == '@') {
                pos_part2 = {row_part2.size(), y};
                row_part2.insert(row_part2.end(), {'.', '.'});
            }
        }
        map_part1.push_back(row_part1);
        map_part2.push_back(row_part2);
    }

    char move;
    std::vector<char> moves;
    while (file >> move) moves.push_back(move);

    std::cout << "Result (part 1): " << solve(map_part1, pos_part1, moves) << std::endl;
    std::cout << "Result (part 2): " << solve(map_part2, pos_part2, moves) << std::endl;
}

int solve(std::vector<std::vector<char>> map, std::pair<int,int> pos, std::vector<char> moves) {
    int height = map.size();
    int width = map[0].size();
    auto hash_fn = [width](const std::pair<int,int> &v) { return v.first + width * v.second; };

    for (char movement : moves) {
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
            std::unordered_set<std::pair<int,int>, decltype(hash_fn)> first(10, hash_fn); first.insert(pos);
            std::vector<std::unordered_set<std::pair<int,int>, decltype(hash_fn)>> moved {first};
            bool can_move = true;
            int y;
            while (can_move) {
                std::unordered_set<std::pair<int, int>, decltype(hash_fn)> next_row(10, hash_fn);
                bool no_more = true;
                for (auto p : moved.back()) {
                    char next = map[p.second+1][p.first];
                    if (next == '#') {
                        can_move = false;
                        break;
                    }
                    if (next == '[') {
                        next_row.insert({p.first, p.second+1});
                        next_row.insert({p.first+1, p.second+1});
                        no_more = false;
                    }
                    if (next == ']') {
                        next_row.insert({p.first, p.second+1});
                        next_row.insert({p.first-1, p.second+1});
                        no_more = false;
                    }
                    if (next == 'O') {
                        next_row.insert({p.first, p.second+1});
                        no_more = false;
                    }
                }
                if (no_more) break;
                moved.push_back(next_row);
            }
            if (!can_move) continue;
            for (auto it = moved.rbegin(); it != moved.rend(); it++) {
                for (auto pos : *it) {
                    map[pos.second+1][pos.first] = map[pos.second][pos.first];
                    map[pos.second][pos.first] = '.';
                }
            }
            pos.second++;
        }
        else if (movement == '^') {
            std::unordered_set<std::pair<int,int>, decltype(hash_fn)> first(10, hash_fn); first.insert(pos);
            std::vector<std::unordered_set<std::pair<int,int>, decltype(hash_fn)>> moved {first};
            bool can_move = true;
            int y;
            while (can_move) {
                std::unordered_set<std::pair<int, int>, decltype(hash_fn)> next_row(10, hash_fn);
                bool no_more = true;
                for (auto p : moved.back()) {
                    char next = map[p.second-1][p.first];
                    if (next == '#') {
                        can_move = false;
                        break;
                    }
                    if (next == '[') {
                        next_row.insert({p.first, p.second-1});
                        next_row.insert({p.first+1, p.second-1});
                        no_more = false;
                    }
                    if (next == ']') {
                        next_row.insert({p.first, p.second-1});
                        next_row.insert({p.first-1, p.second-1});
                        no_more = false;
                    }
                    if (next == 'O') {
                        next_row.insert({p.first, p.second-1});
                        no_more = false;
                    }
                }
                if (no_more) break;
                moved.push_back(next_row);
            }
            if (!can_move) continue;
            for (auto it = moved.rbegin(); it != moved.rend(); it++) {
                for (auto pos : *it) {
                    map[pos.second-1][pos.first] = map[pos.second][pos.first];
                    map[pos.second][pos.first] = '.';
                }
            }
            pos.second--;
        }
    }

    int result = 0;
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            if (map[y][x] == '[' || map[y][x] == 'O') result += x + 100 * y;
        }
    }

    return result;
}

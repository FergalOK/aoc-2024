#include <iostream>
#include <fstream>
#include <cassert>
#include <vector>
#include <stack>
#include <unordered_map>

std::unordered_map<char, int> numeric {
    {'7', 0}, {'8', 1}, {'9', 2},
    {'4', 3}, {'5', 4}, {'6', 5},
    {'1', 6}, {'2', 7}, {'3', 8},
              {'0', 10}, {'A', 11},
};

std::unordered_map<char, int> directional {
              {'^', 1}, {'A', 2},
    {'<', 3}, {'v', 4}, {'>', 5}
};

std::vector<std::vector<char>> paths(int start, int end, std::vector<char> prev, bool num) {
    if (!num && start == 0) return {};
    if (num && start == 9) return {};
    if (start == end) {
        prev.push_back('A');
        return { prev };
    };

    int dx = (end % 3) - (start % 3);
    int dy = (end - start - dx) / 3;

    std::vector<std::vector<char>> result;
    if (dx != 0) {
        char dir = dx > 0 ? '>' : '<';
        int step = dx > 0 ? 1 : -1;
        std::vector<char> next = prev;
        next.push_back(dir);
        auto solve = paths(start + step, end, next, num);
        result.insert(result.end(), solve.begin(), solve.end());
    }
    if (dy != 0) {
        char dir = dy > 0 ? 'v' : '^';
        int step = dy > 0 ? 3 : -3;
        std::vector<char> next = prev;
        next.push_back(dir);
        auto solve = paths(start + step, end, next, num);
        result.insert(result.end(), solve.begin(), solve.end());
    }

    return result;
}

std::vector<std::vector<char>> solve_numerical(std::string code, int position) {
    int prev = position;
    std::vector<std::vector<char>> subpaths;
    for (char dir : code) {
        std::vector<std::vector<char>> newsubpaths;
        int target = numeric[dir];
        auto suffix = paths(prev, target, {}, true);
        prev = target;
        if (subpaths.size() == 0) { subpaths = suffix; continue; }
        for (auto p : suffix) {
            for (auto subp : subpaths) {
                auto copy = subp;
                copy.insert(copy.end(), p.begin(), p.end());
                newsubpaths.push_back(copy);
            }
        }
        subpaths = newsubpaths;
    }

    return subpaths;
}

std::vector<std::vector<char>> solve_directional(std::vector<char> directions, int position) {
    int prev = position;
    std::vector<std::vector<char>> subpaths;
    int n = 1;
    for (char dir : directions) {
        std::vector<std::vector<char>> newsubpaths;
        int target = directional[dir];
        auto suffix = paths(prev, target, {}, false);
        prev = target;
        if (subpaths.size() == 0) { subpaths = suffix; continue; }
        for (auto p : suffix) {
            for (auto subp : subpaths) {
                auto copy = subp;
                copy.insert(copy.end(), p.begin(), p.end());
                newsubpaths.push_back(copy);
            }
        }
        subpaths = newsubpaths;
    }

    return subpaths;
}


int main(int argc,  char** argv) {
    assert(argc == 2);
    std::ifstream file(argv[1]);

    int result = 0;
    for (std::string line; std::getline(file, line);) {
        long min = 100000;
        for (auto num : solve_numerical(line, numeric['A'])) {
            for (auto a : num) std::cout << a; std::cout << std::endl;
            auto dirs0 = solve_directional(num, directional['A']);
            for (auto dir : dirs0) {
                auto dirs = solve_directional(dir, directional['A']);
                for (auto d : dirs) {
                    if (d.size() < min) {
                        min = d.size();
                    }
                }
            }
        }
        result += min * std::stoi(line.substr(0, line.size()-1));
    }
 
    std::cout << "Result (part 1): " << result << std::endl;
}

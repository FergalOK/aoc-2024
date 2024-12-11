#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cassert>
#include <unordered_set>
#include <stack>

int calculate(std::vector<std::pair<int,int>> start_nodes, std::vector<std::vector<char>> map, bool part1 = false);

int main(int argc,  char** argv) {
    assert(argc == 2);
    std::ifstream file;
    file.open(argv[1], std::ios_base::in);

    std::vector<long> values;
    int v;
    while (file >> v) values.push_back(v);

    for (int j = 0; j < 25; j++) {
        size_t size = values.size();
        for (int i = 0; i < size; i++) {
            if (values[i] == 0) {
                values[i] = 1;
                continue;
            }

            std::string s = std::to_string(values[i]);
            if (s.size() % 2 == 0) {
                values[i] = stol(s.substr(0, s.size() / 2));
                values.push_back(stol(s.substr(s.size() / 2)));
                continue;
            }

            values[i] = 2024 * values[i];
        }

        std::cout << "After " << j << " iteration: " << size << std::endl;
    }

    std::cout << "Result (part 1): " << values.size() << std::endl;
}

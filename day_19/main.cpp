#include <iostream>
#include <fstream>
#include <sstream>
#include <cassert>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <stack>
#include <string.h>

std::vector<std::string> towels;
std::unordered_map<std::string, long long> seen;

long solve(std::string design) {
    if (design == "") return 1;
    if (seen.find(design) != seen.end()) return seen[design];

    long result = 0;
    for (std::string t : towels) {
        if (design.compare(0, t.size(), t) == 0) {
            result += solve(design.substr(t.size()));
        }
    }
    seen.insert({design, result});
    return result;
}

int main(int argc,  char** argv) {
    assert(argc == 2);
    std::ifstream file(argv[1]);

    std::string line;
    std::getline(file, line);
    int start = 0;
    while (true) {
        int comma = line.find(", ", start);
        towels.push_back(line.substr(start, comma-start));
        if (comma == -1) break; // substr works because overflow ;)
        start = comma + 2;
    }

    std::getline(file, line); assert(line == "");

    int part_1 = 0;
    long part_2 = 0;
    long count;
    for (std::string design; std::getline(file, design);) {
        long result = solve(design);
        part_1 += result != 0;
        part_2 += result;
    }

    std::cout << "Result (part 1): " << part_1 << std::endl;
    std::cout << "Result (part 2): " << part_2 << std::endl;
}

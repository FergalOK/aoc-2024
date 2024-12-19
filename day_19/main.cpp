#include <iostream>
#include <fstream>
#include <sstream>
#include <cassert>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <stack>
#include <string.h>

int main(int argc,  char** argv) {
    assert(argc == 2);
    std::ifstream file(argv[1]);

    std::string line;
    std::getline(file, line);
    std::vector<std::string> towels;
    int start = 0;
    int comma = line.find(", ", start);
    while (comma != -1) {
        towels.push_back(line.substr(start, comma-start));
        start = comma + 2;
        comma = line.find(", ", start);
    }

    std::getline(file, line); assert(line == "");

    int count = 0;
    for (std::string design; std::getline(file, design);) {
        std::stack<std::string> substr;
        substr.push(design);
        while (!substr.empty()) {
            std::string subdesign = substr.top(); substr.pop();
            if (subdesign == "") {
                count++;
                break;
            }
            for (auto t : towels) {
                if (subdesign.compare(0, t.size(), t) == 0) {
                    substr.push(subdesign.substr(t.size()));
                }
            }
        }
    }

    std::cout << "Result (part 1): " << count << std::endl;
}

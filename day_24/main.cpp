#include <iostream>
#include <fstream>
#include <cassert>
#include <unordered_set>
#include <set>
#include <unordered_map>
#include <regex>
#include <bitset>

int main(int argc,  char** argv) {
    assert(argc == 2);
    std::ifstream file(argv[1]);

    std::regex re0("(.*): ([01])");
    std::unordered_map<std::string,bool> values;
    for (std::string line; std::getline(file, line) && line != "";) {
        std::smatch m;
        std::regex_match(line, m, re0);
        values[m[1]] = m[2] == "1";
    }

    std::vector<std::string> lines;
    for (std::string line; std::getline(file, line);) lines.push_back(line);

    std::regex re1("(.*) (.*) (.*) -> (.*)");
    long long result = 0;
    bool complete = false;
    while (!complete) {
        complete = true;
        for (auto line : lines) {
            std::smatch m;
            std::regex_match(line, m, re1);
            if (values.find(m[1]) == values.end() || values.find(m[3]) == values.end()) {
                complete = false;
                continue;
            }
            if (m[2] == "AND") values[m[4]] = values[m[1]] & values[m[3]];
            else if (m[2] == "OR") values[m[4]] = values[m[1]] | values[m[3]];
            else if (m[2] == "XOR") values[m[4]] = values[m[1]] ^ values[m[3]];
            else throw std::exception();

            if (m[4].str().find('z') == 0) result |= (long long)values[m[4]] << stoi(m[4].str().substr(1));
        }
    }

    std::cout << "Result (part 1): " << result << " (" << std::bitset<64>(result) << ")" << std::endl;
}

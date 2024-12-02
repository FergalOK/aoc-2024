#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <queue>
#include <cassert>

bool isSafe(std::queue<int> &line) {
    int next, prev;
    prev = line.front(); line.pop();
    next = line.front(); line.pop();

    bool increasing = next > prev;
    while (true) {
        if (increasing && !(next > prev && next <= prev + 3)) return false;
        if (!increasing && !(next < prev && next >= prev - 3)) return false;
        if (line.empty()) break;
        prev = next;
        next = line.front(); line.pop();
    }

    return true; 
}

// I hate this so much
// TODO: Find linear solution that handles all edge cases...
bool isDampenerSafe(std::string &line) {
    std::istringstream line_stream(line);
    std::vector<int> values;
    int val;
    while (line_stream >> val) values.push_back(val);

    for (size_t i = 0; i < values.size(); i++) {
        std::queue<int> substring;
        for (size_t j = 0; j < values.size(); j++) {
            if (i == j) continue;
            substring.push(values[j]);
        }
        if (isSafe(substring)) return true;
    }

    return false;
}

int main(int argc,  char** argv) {
    assert(argc == 2);
    std::ifstream file;
    file.open(argv[1], std::ios_base::in);

    int count = 0;
    std::string line;
    while (std::getline(file, line)) {
        count += isDampenerSafe(line);
    }

    std::cout << count << std::endl;
}

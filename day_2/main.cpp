#include <iostream>
#include <fstream>
#include <sstream>
#include <set>
#include <cassert>

bool isSafe(std::string &line) {
    std::istringstream line_stream(line);
    int next, prev;
    if (!(line_stream >> prev >> next)) return true;

    bool increasing = next > prev;
    do {
        if (increasing && !(next > prev && next <= prev + 3)) return false;
        if (!increasing && !(next < prev && next >= prev - 3)) return false;
        prev = next;
    } while (line_stream >> next);

    return true; 
}

int main(int argc,  char** argv) {
    assert(argc == 2);
    std::ifstream file;
    file.open(argv[1], std::ios_base::in);

    int count = 0;
    std::string line;
    while (std::getline(file, line)) {
        count += isSafe(line);
    }

    std::cout << count << std::endl;
}

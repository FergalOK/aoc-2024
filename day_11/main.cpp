#include <iostream>
#include <fstream>
#include <cassert>
#include <unordered_map>

std::unordered_map<long, long> seen;
auto hash = [](long start, int iterations) { return iterations + 75 * start; };

long count(long start, int iterations) {
    if (iterations == 0) return 1;
    if (seen.find(hash(start, iterations)) != seen.end()){
        return seen[hash(start, iterations)];
    }
    
    long result;
    if (start == 0) {
        result = count(1, iterations - 1);
    }
    else {
        std::string s = std::to_string(start);
        if (s.size() % 2 == 0) {
            long left = stol(s.substr(0, s.size() / 2));
            long right = stol(s.substr(s.size() / 2));
            result = count(left, iterations - 1) + count(right, iterations - 1);
        }
        else {
            result = count(2024 * start, iterations - 1);
        }
    }

    seen.insert({hash(start, iterations), result});
    return result;
}

int main(int argc,  char** argv) {
    assert(argc == 2);
    std::ifstream file;
    file.open(argv[1], std::ios_base::in);

    int v;
    long result_part1 = 0;
    long result_part2 = 0;
    while (file >> v) {
        result_part1 += count(v, 25);
        result_part2 += count(v, 75);
    }

    std::cout << "Result (part 1): " << result_part1 << std::endl;
    std::cout << "Result (part 2): " << result_part2 << std::endl;
}

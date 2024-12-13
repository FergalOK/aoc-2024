#include <iostream>
#include <fstream>
#include <cassert>
#include <regex>
#include <limits.h>

/*
xp = a * xa + b * xb
yp = a * ya + b * yb
cost = 3a + b

b = (xp - a * xa) / xb
Replacing b in second formula:
a = (yp * xb - xp * yb) / (ya * xb - xa * yb)
*/

long calculate(long xa, long ya, long xb, long yb, long xp, long yp) {
    long a_num = yp * xb - xp * yb;
    long a_denom = ya * xb - xa * yb;
    if (a_num % a_denom != 0) return 0;
    long a = a_num / a_denom;
    if (a < 0) return 0;

    long b_num = xp - a * xa;
    if (b_num % xb != 0) return 0;
    long b = b_num / xb;
    if (b < 0) return 0;

    return 3 * a + b;
}

int main(int argc,  char** argv) {
    assert(argc == 2);
    std::ifstream file(argv[1]);
    std::ostringstream buffer;
    buffer << file.rdbuf();
    std::string input = buffer.str();

    long result_part1 = 0;
    long result_part2 = 0;
    std::regex reg("Button A: X\\+(\\d+), Y\\+(\\d+)\nButton B: X\\+(\\d+), Y\\+(\\d+)\nPrize: X=(\\d+), Y=(\\d+)");
    auto iter = std::sregex_iterator(input.begin(), input.end(), reg);
    for (std::sregex_iterator i = iter; i != std::sregex_iterator(); i++) {
        std::smatch match = *i;
        result_part1 += calculate(stoi(match[1]), stoi(match[2]),
                                  stoi(match[3]), stoi(match[4]),
                                  stol(match[5]), stol(match[6]));

        result_part2 += calculate(stoi(match[1]), stoi(match[2]),
                                  stoi(match[3]), stoi(match[4]),
                                  10000000000000 + stol(match[5]),
                                  10000000000000 + stol(match[6]));
    }

    std::cout << "Result (part 1): " << result_part1 << std::endl;
    std::cout << "Result (part 2): " << result_part2 << std::endl;
}

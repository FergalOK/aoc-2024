#include <iostream>
#include <fstream>
#include <cassert>
#include <regex>
#include <limits.h>

int calculate(int x_a, int y_a, int x_b, int y_b, int x_p, int y_p) {
    // Note: BRUTE FORCE!
    int min = INT_MAX;
    for (int a = 0; a <= 100; a++) {
        int b = (x_p - a * x_a) / x_b;
        if (a * x_a + b * x_b == x_p && a * y_a + b * y_b == y_p) {
            int cost = 3 * a + b;
            if (cost < min) min = cost;
        }
    }

    if (min == INT_MAX) return 0;
    return min;
}

int main(int argc,  char** argv) {
    assert(argc == 2);
    std::ifstream file(argv[1]);
    std::ostringstream buffer;
    buffer << file.rdbuf();
    std::string input = buffer.str();

    int result = 0;
    std::regex reg("Button A: X\\+(\\d+), Y\\+(\\d+)\nButton B: X\\+(\\d+), Y\\+(\\d+)\nPrize: X=(\\d+), Y=(\\d+)");
    auto iter = std::sregex_iterator(input.begin(), input.end(), reg);
    for (std::sregex_iterator i = iter; i != std::sregex_iterator(); i++) {
        std::smatch match = *i;
        result += calculate(stoi(match[1]), stoi(match[2]),
                            stoi(match[3]), stoi(match[4]),
                            stoi(match[5]), stoi(match[6]));
    }

    std::cout << "Result: " << result << std::endl;
}

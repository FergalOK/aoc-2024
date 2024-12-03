#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <queue>
#include <regex>
#include <numeric>
#include <cassert>

int calculate(std::string text) {
    int result = 0;
    std::regex reg("mul\\((\\d{1,3}),(\\d{1,3})\\)");
    auto it = std::sregex_iterator(text.begin(), text.end(), reg);
    auto it_end = std::sregex_iterator();
    for (; it != it_end; it++) {
        result += atoi((*it)[1].str().c_str()) * atoi((*it)[2].str().c_str());
    }

    return result;
}

int main(int argc,  char** argv) {
    assert(argc == 2);
    std::ifstream file;
    file.open(argv[1], std::ios_base::in);
    std::string input = std::string(std::istreambuf_iterator<char>(file),
                                    std::istreambuf_iterator<char>());

    int result = 0;

    std::smatch match;
    std::regex reg_do("do\\(\\)");
    std::regex reg_dont("don't\\(\\)");
    int do_index = 0;
    while (true) {
        input = input.substr(do_index + sizeof("do()") - 1);
        if (!std::regex_search(input, match, reg_dont)) {
            result += calculate(input);
            break;
        }
        int dont_index = match.position();
        result += calculate(input.substr(0, dont_index));
        input = input.substr(dont_index + sizeof("don't()") - 1);
        if (!std::regex_search(input, match, reg_do)) break;
        do_index = match.position();
    }

    std::cout << result << std::endl;
}

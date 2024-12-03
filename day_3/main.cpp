#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <queue>
#include <regex>
#include <numeric>
#include <cassert>

int main(int argc,  char** argv) {
    assert(argc == 2);
    std::ifstream file;
    file.open(argv[1], std::ios_base::in);
    std::string example = std::string(std::istreambuf_iterator<char>(file),
                                      std::istreambuf_iterator<char>());

    int result = 0;
    std::regex reg("mul\\((\\d{1,3}),(\\d{1,3})\\)");
    auto it = std::sregex_iterator(example.begin(), example.end(), reg);
    auto it_end = std::sregex_iterator();
    for (; it != it_end; it++) {
        result += atoi((*it)[1].str().c_str()) * atoi((*it)[2].str().c_str());
    }
    
    std::cout << result << std::endl;
}

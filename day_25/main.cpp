#include <iostream>
#include <fstream>
#include <cassert>
#include <unordered_set>
#include <set>
#include <unordered_map>
#include <regex>

const int KEY_SIZE = 7;

int main(int argc,  char** argv) {
    assert(argc == 2);
    std::ifstream file(argv[1]);
    std::vector<std::vector<int>> keys;
    std::vector<std::vector<int>> locks;

    std::string line;
    do {
        std::vector<std::string> input;
        for (int i = 0; i < KEY_SIZE; i++) {
            std::getline(file, line);
            input.push_back(line);
        }

        std::vector<int> compressed;
        if (input[0] == "#####") {
            for (int i = 0; i < 5; i++) {
                for (int j = 0; j < KEY_SIZE; j++) {
                    if (input[j][i] != '#') {
                        compressed.push_back(j-1);
                        break;
                    }
                }
            }
            locks.push_back(compressed);
        }
        else {
            assert(input[KEY_SIZE-1] == "#####");
            for (int i = 0; i < 5; i++) {
                for (int j = 0; j < KEY_SIZE; j++) {
                    if (input[j][i] == '#') {
                        compressed.push_back(KEY_SIZE - j - 1);
                        break;
                    }
                }
            }
            keys.push_back(compressed);
        }
    } while (std::getline(file, line) && line == "");
    
    std::cout << "Keys\n";
    for (auto k : keys) {
        for (auto a : k) std::cout << a << ",";
        std::cout << std::endl;
    }
    std::cout << "Locks\n";
    for (auto k : locks) {
        for (auto a : k) std::cout << a << ",";
        std::cout << std::endl;
    }

    auto is_match = [](std::vector<int> lock, std::vector<int> key) {
        for (int i = 0; i < key.size(); i++) {
            if (key[i] + lock[i] > KEY_SIZE - 2) return 0;
        }
        return 1;
    };

    int result = 0;
    for (auto lock : locks) {
        for (auto key : keys) {
            result += is_match(lock, key);
        }
    }

    std::cout << "Result (part 1): " << result << std::endl;
}

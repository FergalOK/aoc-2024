#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cassert>
#include <unordered_map>
#include <unordered_set>

int main(int argc,  char** argv) {
    assert(argc == 2);
    std::ifstream file;
    file.open(argv[1], std::ios_base::in);

    std::vector<char> input;
    char val;
    while (file >> val) input.push_back(val - '0');

    std::stringstream buffer;
    int file_id = 0;
    long compressed = 0;
    int checksum_count = 0;
    int end_pointer = input.size() - 1 - (input.size() - 1) % 2;
    int end_pointer_used = 0;
    for (int i = 0; i < end_pointer; i++) {
        if (i % 2 == 0) {
            // TODO: No loop
            for (int j = 0; j < input[i]; j++) {
                compressed += checksum_count++ * file_id;
            }
            file_id++;
        }
        else {
            for (int j = 0; j < input[i]; j++) {
                // Pop one from back
                int last = input[end_pointer];
                end_pointer_used++;

                compressed += checksum_count++ * int(end_pointer / 2);

                if (end_pointer_used >= input[end_pointer]) {
                    end_pointer -= 2;
                    end_pointer_used = 0;
                    // std::cout << "End pointer "<< end_pointer << ", i: " << i << std::endl;
                    if (end_pointer < i) {
                        break;
                    }
                }
            }
        }
    }

    for (int k = 0; k < input[end_pointer] - end_pointer_used; k++) {
        compressed += checksum_count++ * int(end_pointer / 2);
    }

    std::cout << "Result " << compressed << std::endl;

}

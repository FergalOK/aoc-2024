#include <iostream>
#include <fstream>
#include <vector>
#include <cassert>
#include <unordered_set>

long part_1(std::vector<char> input);
long part_2(std::vector<char> input);

int main(int argc,  char** argv) {
    assert(argc == 2);
    std::ifstream file;
    file.open(argv[1], std::ios_base::in);

    std::vector<char> input;
    char val;
    while (file >> val) input.push_back(val - '0');

    std::cout << "Result (part 1): " << part_1(input) << std::endl;
    std::cout << "Result (part 2): " << part_2(input) << std::endl;
}

long part_1(std::vector<char> input) {
    int file_id = 0;
    long compressed = 0;
    int checksum_count = 0;
    int end_pointer = input.size() - 1 - (input.size() - 1) % 2;
    int end_pointer_used = 0;
    for (int i = 0; i < end_pointer; i++) {
        if (i % 2 == 0) {
            compressed += input[i] * long(checksum_count * file_id + (checksum_count+input[i]-1) * file_id) / 2;
            checksum_count += input[i];
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

    return compressed;
}

long part_2(std::vector<char> input) {
    int file_id = 0;
    long compressed = 0;
    int checksum_count = 0;
    int end_pointer = input.size() - 1 - (input.size() - 1) % 2;
    std::unordered_set<int> moved;
    for (int i = 0; i < input.size(); i++) {
        if (i % 2 == 0) {
            if (moved.find(i) != moved.end()) {
                file_id++;
                checksum_count += input[i];
                continue;
            }
            compressed += input[i] * long(checksum_count * file_id + (checksum_count+input[i]-1) * file_id) / 2;
            checksum_count += input[i];
            file_id++;
        }
        else {
            int end_pointer_used = 0;
            for (int j = end_pointer; j > i; j -= 2) {
                if (input[j] <= input[i] - end_pointer_used && moved.find(j) == moved.end()) {
                    moved.insert(j);
                    for (int k = 0; k < input[j]; k++) {
                        compressed += checksum_count++ * int(j / 2);
                    }
                    end_pointer_used += input[j];
                    if (input[i] - end_pointer_used == 0) break;
                }
            }
            checksum_count += input[i] - end_pointer_used;
        }
    }

    return compressed;
}

#include <iostream>
#include <fstream>
#include <sstream>
#include <cassert>
#include <vector>
#include <unordered_map>

long combo(int lit, unsigned long reg[]) {
    switch (lit) {
        case 0: case 1: case 2: case 3: return lit;
        case 4: return reg[0];
        case 5: return reg[1];
        case 6: return reg[2];
        default: std::cout << "Unexpected operand " << lit << std::endl; exit(1);
    }
};

std::vector<int> interpret(std::vector<int> program, unsigned long init_reg[3]) {
    unsigned long reg[3] { init_reg[0], init_reg[1], init_reg[2] };
    int ip = 0;
    std::vector<int> output;
    while (ip+1 < program.size()) {
        if (program[ip] == 0) reg[0] = reg[0] / (1 << combo(program[ip+1], reg));
        else if (program[ip] == 1) reg[1] = reg[1] ^ program[ip+1];
        else if (program[ip] == 2) reg[1] = combo(program[ip+1], reg) % 8;
        else if (program[ip] == 3) {
            if (reg[0]) {
                ip = program[ip+1];
                continue;
            }
        }
        else if (program[ip] == 4) reg[1] = reg[1] ^ reg[2];
        else if (program[ip] == 5) output.push_back(combo(program[ip+1], reg) % 8);
        else if (program[ip] == 6) reg[1] = reg[0] / (1 << combo(program[ip+1], reg));
        else if (program[ip] == 7) reg[2] = reg[0] / (1 << combo(program[ip+1], reg));

        ip += 2;
    }


    return output;
}

unsigned long reg[3];
std::vector<int> program;

unsigned long part_2(unsigned long current, unsigned long i) {
    if (i == -1) {
        std::cout << "Result (part 2): " << current << std::endl;
        return -1;
    }

    for (unsigned long j = 0; j < 8; j++) {
        unsigned long test[3] { current + (j << (3 * i)), reg[1], reg[2] };
        auto vals = interpret(program, test);
        if (vals.size() >= i && vals[i] == program[i]) {
            if (part_2(current + (j << (3 * i)), i - 1) != -1) return j;
        }
    }

    return -1;
};

int main(int argc,  char** argv) {
    assert(argc == 2);
    std::ifstream file(argv[1]);

    std::string line;
    for (int i = 0; i < 3; i++) {
        std::getline(file, line);
        reg[i] = stol(line.substr(sizeof("Register X: ")-1));
    }
    std::getline(file, line); assert(line == "");

    std::getline(file, line);
    std::stringstream ss(line.substr(sizeof("Program: ")-1));
    int word; char comma;
    while (ss >> word) {
        program.push_back(word);
        ss >> comma;
    }

    auto output = interpret(program, reg);
    std::cout << "Result (part 1): " << output[0];
    for (size_t i = 1; i < output.size(); i++) {
        std::cout << "," << output[i];
    }
    std::cout << std::endl;

    part_2(0, program.size()-1);
}

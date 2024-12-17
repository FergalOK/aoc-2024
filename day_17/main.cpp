#include <iostream>
#include <fstream>
#include <sstream>
#include <cassert>
#include <vector>

int combo(int lit, int reg[]) {
    switch (lit) {
        case 0: case 1: case 2: case 3: return lit;
        case 4: return reg[0];
        case 5: return reg[1];
        case 6: return reg[2];
        default: std::cout << "Unexpected operand " << lit << std::endl; exit(1);
    }
};

int main(int argc,  char** argv) {
    assert(argc == 2);
    std::ifstream file(argv[1]);

    int reg[3];
    std::vector<int> program;

    std::string line;
    for (int i = 0; i < 3; i++) {
        std::getline(file, line);
        reg[i] = stoi(line.substr(sizeof("Register X: ")-1));
    }
    std::getline(file, line); assert(line == "");

    std::getline(file, line);
    std::stringstream ss(line.substr(sizeof("Program: ")-1));
    int word; char comma;
    while (ss >> word) {
        program.push_back(word);
        ss >> comma;
    }

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

    std::cout << output[0];
    for (size_t i = 1; i < output.size(); i++) {
        std::cout << "," << output[i];
    }
    std::cout << std::endl;
}


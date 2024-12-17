#include <iostream>
#include <fstream>
#include <sstream>
#include <cassert>
#include <vector>
#include <unordered_map>

enum Type {
    VALUE, 
};

struct node {
    int type;
    node *left = nullptr;
    node *right = nullptr;
};

long combo(int lit, unsigned long reg[]) {
    switch (lit) {
        case 0: case 1: case 2: case 3: return lit;
        case 4: return reg[0];
        case 5: return reg[1];
        case 6: return reg[2];
        default: std::cout << "Unexpected operand " << lit << std::endl; exit(1);
    }
};
std::unordered_map<int, std::string> opname {
    {0, "a <- a / (2 ^ combo)"},
    {1, "b <- b xor lit"},
    {2, "b <- combo % 8"},
    {3, "jump"},
    {4, "b <- b ^ c"},
    {5, "out <- combo % 8"},
    {6, "b <- a / 2 ^ combo"},
    {7, "c <- a / 2 ^ combo"}
};

std::string display(int opcode, int lit, unsigned long reg[3]) {
    switch (opcode) {
        case 0: return "a <- " + std::to_string(reg[0]) + " / (2 ** " + std::to_string(combo(lit, reg)) + ")";
        case 1: return "b <- " + std::to_string(reg[1]) + " xor " + std::to_string(lit);
        case 2: return "b <- " + std::to_string(combo(lit, reg)) + " % 8";
        case 3: return "jump";
        case 4: return "b <- " + std::to_string(reg[1]) + " ^ " + std::to_string(reg[2]);
        case 5: return "out <- " + std::to_string(combo(lit, reg)) + " % 8";
        case 6: return "b <- " + std::to_string(reg[0]) + " / (2 ** " + std::to_string(combo(lit, reg)) + ")";
        case 7: return "c <- " + std::to_string(reg[0]) + " / (2 ** " + std::to_string(combo(lit, reg)) + ")";
        default: return "";
    }
}

std::vector<int> interpret(std::vector<int> program, unsigned long init_reg[3]) {
    unsigned long reg[3] { init_reg[0], init_reg[1], init_reg[2] };
    int ip = 0;
    std::vector<int> output;
    while (ip+1 < program.size()) {
        // std::cout << "A, B, C: " << reg[0] << ", " << reg[1] << ", " << reg[2] << std::endl;
        // for (auto mem : program) std::cout << mem << ",";
        // std::cout << std::endl;
        // for (int i = 0; i < ip; i++) std::cout << "  ";
        // std::cout << "^" << std::endl;
        // std::cout << opname[program[ip]] << std::endl;
        // std::cout << display(program[ip], program[ip+1], reg) << std::endl;
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

#include <functional>
unsigned long reg[3];
std::vector<int> program;

unsigned long f(unsigned long current, unsigned long i, std::vector<int> &answer) {
    std::vector<unsigned long> potential;
    if (i == -1) {
        std::cout << "Result (part 2): " << current << std::endl;
        return 0;
    }

    for (unsigned long j = 0; j < 8; j++) {
        unsigned long test[3] { current + (j << (3 * i)), reg[1], reg[2] };
        auto vals = interpret(program, test);
        // std::cout << test[0] << ": " << i << std::endl;
        if (vals.size() >= i && vals[i] == program[i]) {
            potential.push_back(j);
            std::cout << "At " << i << " Maybe " << j << std::endl;
        }
    }

    for (auto p : potential) {
        int j = f(current + (p << (3 * i)), i - 1, answer);
        if (j != -1) {
            std::cout << "At " << i - 1 << " need " << j << std::endl;
            answer.push_back(j);
            return p;
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

    // reg[0] = 52042869;
    auto output = interpret(program, reg);

    std::cout << "Result (part 1): " << output[0];
    for (size_t i = 1; i < output.size(); i++) {
        std::cout << "," << output[i];
    }
    std::cout << std::endl;

    unsigned long result = 0;
    std::vector<int> solution;
    f(result, program.size()-1, solution);
    for (auto s : solution) std::cout << s << ", ";
    std::cout << std::endl;


    for (long skip = 0; skip < 1; skip++) {
        int skipped = 0;
        unsigned long result = 0;
        for (int i = program.size() - 1; i >= 0; i--) {
            std::cout << "i " << i << std::endl;
            unsigned long j;
            std::vector<int> potential;
            for (j = 0; j < 8; j++) {
                unsigned long test[3] { result + (j << (3 * i)), reg[1], reg[2] };
                auto vals = interpret(program, test);
                if (vals.size() >= i && vals[i] == program[i]) {
                    potential.push_back(j);
                    std::cout << "Getting somewhere " << vals[i] << " == " << program[i] << std::endl;
                    std::cout << "A = " << test[0] << " using j=" << j << std::endl;
                    result = test[0];
                    std::cout << "Test: " << vals[0];
                    for (size_t i = 1; i < vals.size(); i++) {
                        std::cout << "," << vals[i];
                    }
                    std::cout << std::endl;
                    break;
                }
            }
            // if (!potential.empty()) {
            //     result |= potential[0] << (3 * i);
            // }
            // std::cout << "Outside " << i << " " << potential.size() <<  std::endl;
            // for (auto p : potential) std::cout << "Potential " << p << std::endl;
            if (result < (1 << (3 * i))) std::cout << "Skip" << std::endl;
        }
    }
}


/*
a0
b1 = a0 % 8
b2 = b1 ^ 7
c1 = a0 / (2 ** b2)
a1 = a0 / (2 ** 3)
b3 = b2 ^ c1
b4 = b3 ^ 7
out <- b4 % 8
jmp
*/

/* 123456789
a0
out <- ((a0 % 8) ^ (a0 >> (~(a0 & 7))) % 8
a1 = a0 >> 3
out <- ((a1 % 8) ^ (a1 >> ~(a1 & 7)) % 8
a2 = a1 >> 3

jmp (keep a0)
*/
/*
0 -> 0
1 -> (1 ) % 8
2 -> 
3 -> 
4 -> 
5 -> 
6 -> 
7 -> 
*/
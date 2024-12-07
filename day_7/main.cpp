#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cassert>

int main(int argc,  char** argv) {
    assert(argc == 2);
    std::ifstream file;
    file.open(argv[1], std::ios_base::in);

    long result = 0;
    std::string line;
    while (std::getline(file, line)) {
        long target;
        char colon;
        std::vector<long> vals;
        auto ss = std::stringstream(line);
        assert(ss >> target >> colon);
        int val;
        while (ss >> val) {
            vals.push_back(val);
        }

        long final = 1 << vals.size();
        for (long combination = 0; combination < final; combination++) {
            long test_val = vals[0];
            for (size_t i = 1; i < vals.size(); i++) {
                if (combination & (1 << i)) test_val *= vals[i];
                else test_val += vals[i];
            }
            if (test_val == target) {
                result += target;
                break;
            }
        }
    }

    std::cout << "Result: " << result << std::endl;
}

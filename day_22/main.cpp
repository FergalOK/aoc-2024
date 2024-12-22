#include <iostream>
#include <fstream>
#include <cassert>

long mix(long val, long secret) {
    return val ^ secret;
}

long prune(long val) {
    return val % 16777216;
}

int main(int argc,  char** argv) {
    assert(argc == 2);
    std::ifstream file(argv[1]);

    long result = 0;
    long secret;
    while (file >> secret) {
        for (int i = 0; i < 2000; i++) {
            secret = prune(mix(secret * 64, secret));
            secret = prune(mix(secret / 32, secret));
            secret = prune(mix(secret * 2048, secret));
        }
        result += secret;
    }

    std::cout << "Result (part 1): " << result << std::endl;
}

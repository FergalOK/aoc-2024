#include <iostream>
#include <fstream>
#include <cassert>
#include <unordered_set>
#include <unordered_map>

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
    std::unordered_map<long, long> costs;
    while (file >> secret) {
        long prev = secret;
        long num = 0;
        for (int i = 0; i < 3; i++) {
            secret = prune(mix(secret * 64, secret));
            secret = prune(mix(secret / 32, secret));
            secret = prune(mix(secret * 2048, secret));
            int change = (secret % 10) - (prev % 10);
            num = (change+10) * (20*20*20) + (num / 20);
            prev = secret;
        }

        std::unordered_set<long> seen;
        int max = 0;
        for (int i = 3; i < 2000; i++) {
            secret = prune(mix(secret * 64, secret));
            secret = prune(mix(secret / 32, secret));
            secret = prune(mix(secret * 2048, secret));

            int change = (secret % 10) - (prev % 10);
            num = (change+10) * (20*20*20) + (num / 20);
            prev = secret;
            if (seen.find(num) == seen.end()) {
                if (costs.find(num) == costs.end()) costs[num] = 0;
                costs[num] += secret % 10;
                seen.insert(num);
            }
        }
        result += secret;
    }

    int max = 0;
    for (auto [seq, cost] : costs) {
        if (cost > max) max = cost;
    }

    std::cout << "Result (part 1): " << result << std::endl;
    std::cout << "Result (part 2): " << max << std::endl;
}

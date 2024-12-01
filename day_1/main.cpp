#include <iostream>
#include <fstream>
#include <set>
#include <cassert>

int main(int argc,  char** argv) {
    assert(argc == 2);
    std::ifstream file;
    file.open(argv[1], std::ios_base::in);
    std::string line;

    std::multiset<int> left_multiset, right_multiset;
    int left, right;
    while (file >> left >> right) {
        left_multiset.insert(left);
        right_multiset.insert(right);
    }

    int result = 0;
    auto left_it = left_multiset.begin();
    auto right_it = right_multiset.begin();
    for (; left_it != left_multiset.end(); left_it++, right_it++) {
        result += std::abs(*left_it - *right_it);
    }
    std::cout << result << std::endl;
}

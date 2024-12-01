#include <iostream>
#include <fstream>
#include <set>
#include <cassert>

int main(int argc,  char** argv) {
    assert(argc == 2);
    std::ifstream file;
    file.open(argv[1], std::ios_base::in);

    std::multiset<int> left_multiset, right_multiset;
    int left, right;
    while (file >> left >> right) {
        left_multiset.insert(left);
        right_multiset.insert(right);
    }

    int distance = 0;
    auto right_it = right_multiset.begin();
    for (auto left_it = left_multiset.begin(); left_it != left_multiset.end(); left_it++, right_it++) {
        distance += std::abs(*left_it - *right_it);
    }
    std::cout << "Distance: " << distance << std::endl;

    int similarity = 0;
    for (auto it = left_multiset.begin(); it != left_multiset.end(); it++) {
        similarity += *it * right_multiset.count(*it);
    }
    std::cout << "Similarity: " << similarity << std::endl;
}

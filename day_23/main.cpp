#include <iostream>
#include <fstream>
#include <cassert>
#include <unordered_set>
#include <set>
#include <unordered_map>
#include <regex>

int main(int argc,  char** argv) {
    assert(argc == 2);
    std::ifstream file(argv[1]);
    std::ostringstream buffer;
    buffer << file.rdbuf();
    std::string input = buffer.str();

    std::regex re("([a-z]{2})-([a-z]{2})");

    std::unordered_map<std::string, std::unordered_set<std::string>> computers;
    std::vector<std::pair<std::string,std::string>> vertices;
    auto it = std::sregex_iterator(input.begin(), input.end(), re);
    for (it; it != std::sregex_iterator(); it++) {
        std::smatch match = *it;
        vertices.push_back({match[1], match[2]});
        if (computers.find(match[1]) == computers.end()) computers[match[1]] = std::unordered_set<std::string>();
        if (computers.find(match[2]) == computers.end()) computers[match[2]] = std::unordered_set<std::string>();
        computers[match[1]].insert(match[2]);
        computers[match[2]].insert(match[1]);
    }

    int result = 0;
    for (auto it0 = computers.begin(); it0 != computers.end(); it0++) {
        auto set0 = it0->second;
        auto it1 = it0; std::advance(it1, 1);
        for (it1; it1 != computers.end(); it1++) {
            if (set0.find(it1->first) == set0.end()) continue;

            auto set1 = it1->second;
            auto it2 = it1; std::advance(it2, 1);
            for (it2; it2 != computers.end(); it2++) {
                if (it0->first.find('t') != 0 && it1->first.find('t') != 0 && it2->first.find('t') != 0) continue;
                auto set2 = it2->second;
                if (set0.find(it2->first) != set0.end() && set1.find(it2->first) != set1.end()) {
                    result++;
                 }
            }
        }
    }

    std::cout << "Result (part 1): " << result << std::endl;

    std::set<std::string> max_clique; // Ordered alphabetically!
    int max_size = 0;
    for (auto it = computers.begin(); it != computers.end(); it++) {
        std::set<std::string> clique;
        clique.insert(it->first);
        for (auto it1 = computers.begin(); it1 != computers.end(); it1++) {
            bool in_clique = true;
            for (auto vertex : clique) {
                if (computers[vertex].find(it1->first) == computers[vertex].end()) {
                    in_clique = false;
                    break;
                }
            }
            if (in_clique) clique.insert(it1->first);
        }
        if (clique.size() > max_size) {
            max_clique = clique;
            max_size = clique.size();
        }
    }

    auto clique_it = max_clique.begin();
    std::string a = *clique_it;
    std::cout << "Result (part 2): " << *clique_it++;
    for (clique_it; clique_it != max_clique.end(); clique_it++) {
        std::cout << "," << *clique_it;
    }
    std::cout << std::endl;
}

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cassert>
#include <unordered_map>
#include <unordered_set>

int main(int argc,  char** argv) {
    assert(argc == 2);
    std::ifstream file;
    file.open(argv[1], std::ios_base::in);

    std::string line;
    std::unordered_map<int, std::vector<int>> precedence;
    while (std::getline(file, line) && line != "") {
        auto stream = std::stringstream(line);
        int before, after;
        char ignore;
        stream >> before >> ignore >> after;
        assert(ignore == '|');

        if (precedence.find(after) == precedence.end()) {
            precedence.insert({after, std::vector<int>()});
        }
        precedence[after].push_back(before);
    }

    auto calculate_part1 = [precedence](std::vector<int> pages) {
        std::unordered_set<int> blacklist;
        for (int page : pages) {
            if (blacklist.find(page) != blacklist.end()) {
                return 0;
            }

            if (precedence.find(page) != precedence.end()) {
                std::vector<int> new_filter = precedence.at(page);
                blacklist.insert(new_filter.begin(), new_filter.end());
            }
        }

        return pages[pages.size() / 2];
    };

    auto calculate_part2 = [precedence](std::vector<int> pages) {
        bool sorted = false;
        while (!sorted) {
            std::unordered_map<int, int> blacklist;
            sorted = true;
            for (size_t i = 0; i < pages.size(); i++) {
                int page = pages[i];
                if (blacklist.find(page) != blacklist.end()) {
                    int j = blacklist[page];
                    int tmp = pages[i];
                    pages[i] = pages[j];
                    pages[j] = tmp;
                    sorted = false;
                    break;
                }

                if (precedence.find(page) != precedence.end()) {
                    for (int p : precedence.at(page)) {
                        blacklist.insert({p, i});
                    }
                }
            }
        }

        return pages[pages.size() / 2];
    };

    int result_ordered = 0;
    int result_unordered = 0;
    while (std::getline(file, line)) {
        std::vector<int> pages;
        auto stream = std::stringstream(line);
        int page;
        while (stream >> page) {
            char comma; assert(!(stream >> comma) || comma == ',');
            pages.push_back(page);
        }

        int val = calculate_part1(pages);
        result_ordered += val;
        if (!val) result_unordered += calculate_part2(pages);
    }

    std::cout << "Result " << result_ordered << std::endl;
    std::cout << "Result " << result_unordered << std::endl;
}
#include <vector>
#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <string>
#include <sstream>

std::unordered_map<int, std::vector<int>> rules;

bool contains(const std::vector<int>& list, int x) {
    for (const auto& elt : list) {
        if (elt == x) {
            return true;
        }
    }
    return false;
}

bool validLine(const std::vector<int>& line) {
    // 75,47,61,53,29
    // if rules[47] contains 75, return false
    // if rules[61] contains 75,47, return false
    if (line.size() == 1) {
        return true;
    }
    for (int i = 1; i < line.size(); ++i) {
        if (rules.find(line[i]) == rules.end()) {
            continue;
        }
        
        for (int j = 0; j < i; ++j) {
            if(contains(rules[line[i]], line[j])) {
                return false;
            }
        }
    }
    return true;
}

int main(int argc, char** argv) {
    std::string line;
    while(getline(std::cin, line)) {
        if(line == "") {
            break;
        }
        
        int x, y;
        char pipe;
        std::stringstream ss(line);
        ss >> x >> pipe >> y;
        rules[x].push_back(y);

    }

    int sum = 0;
    while (getline(std::cin, line)) {
        std::stringstream ss(line);
        std::vector<int> lineVec;
        int x;
        char comma;
        ss >> x;
        lineVec.push_back(x);
        while (ss >> comma >> x) {
            lineVec.push_back(x);
        }
        if(validLine(lineVec)) {
            int middleIdx = lineVec.size() / 2;
            sum += lineVec[middleIdx];
        }
    }
    std::cout << sum << std::endl;

    return 0;
}
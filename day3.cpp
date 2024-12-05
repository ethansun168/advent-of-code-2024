#include <vector>
#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <string>
#include <sstream>

bool allowed(const std::vector<char>& allowedChars, char ch) {
    for (const auto& elt : allowedChars) {
        if (ch == elt) {
            return true;
        }
    }
    return false;
}

// Return strings of valid mul commands
std::vector<std::string> positions(std::string line) {
    std::vector<std::string> ret;
    std::string substr = "mul(";
    std::vector<size_t> positions;
    size_t pos = line.find(substr, 0);
    while(pos != std::string::npos) {
        positions.push_back(pos);
        pos = line.find(substr, pos + 1);
    }
    std::vector<char> allowedChars = {'1', '2', '3', '4', '5', '6', '7', '8', '9', '0'};
    for (int i = 0; i < positions.size(); ++i) {
        // Scan up to 8 characters
        bool commaSeen = false;
        bool flag = true;
        int stridx = positions[i] + 4;
        int length = 0;
        for(; length < 8; ++length) {
            int curIdx = stridx + length;

            if (curIdx >= line.size()) {
                flag = false;
                break;
            }
            if (length > 3 && !commaSeen) {
                flag = false;
                break;
            }

            // constraints on characters
            if (commaSeen && line[curIdx - 1] != ',') {
                allowedChars = {'1', '2', '3', '4', '5', '6', '7', '8', '9', ')', '0'};
            }
            else if (!commaSeen && length != 0) {
                allowedChars = {'1', '2', '3', '4', '5', '6', '7', '8', '9', ',', '0'};
            }

            if(!allowed(allowedChars, line[curIdx])) {
                flag = false;
                break;
            }

            if (line[curIdx] == ',') {
                commaSeen = true;
            }
            else if (line[curIdx] == ')') {
                break;
            }
        }
        if (line[stridx + length] != ')') {
            flag = false;
        }
        if (flag) {
            ret.push_back(line.substr(stridx, length));
        }
    }
    return ret;
}

int main(int argc, char** argv) {

    std::string line;
    int mulCount = 0;
    while(getline(std::cin, line)) {
        std::vector<std::string> linePos = positions(line);
        // calculate the muls
        for (const auto& elt : linePos) {
            int x, y;
            char comma;
            std::stringstream ss(elt);
            ss >> x >> comma >> y;
            mulCount += x * y;
        }

    }
    std::cout << mulCount << std::endl;

    return 0;
}
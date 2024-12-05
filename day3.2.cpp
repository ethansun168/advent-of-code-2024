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

std::vector<int> findSubstr(const std::string& line, std::string substr) {
    std::vector<int> positions;
    size_t pos = line.find(substr, 0);
    while(pos != std::string::npos) {
        positions.push_back(pos);
        pos = line.find(substr, pos + 1);
    }
    return positions;
}

// Return strings of valid mul commands
std::vector<std::pair<int, std::string>> positions(std::string line) {
    std::vector<std::pair<int, std::string>> ret;
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
            ret.push_back(std::pair(stridx, line.substr(stridx, length)));
        }
    }
    return ret;
}

int main(int argc, char** argv) {

    std::string line;
    int mulCount = 0;
    bool active = true;
    while(getline(std::cin, line)) {
        std::vector<std::pair<int, std::string>> elts = positions(line);

        std::vector<int> dos = findSubstr(line, "do()");
        std::vector<int> donts = findSubstr(line, "don't()");

        int doIdx = 0;
        int dontIdx = 0;

        for (int i = 0; i < elts.size(); ++i) {
            // do:   [884, 1095, 1858, 2265]
            // dont: [2, 1049, 1273, 2699, 2751]
            // elts: [13, 46, 66, 88, 105, 123, 137...]
            
            // do dont elt
            // dont do elt
            // do elt dont
            // dont elt do
            // elt do dont -- do nothing
            // elt dont do -- do nothing
            
            if (elts[i].first <= dos[doIdx] && elts[i].first <= donts[dontIdx]) {
                // do nothing
            }
            else if(elts[i].first >= dos[doIdx] && elts[i].first >= donts[dontIdx]) {
                // do dont elt, dont do elt
                if (dos[doIdx] > donts[dontIdx]) {
                    // dont do elt
                    if (dontIdx < donts.size() - 1) {
                        ++dontIdx;
                    }
                    active = true;
                }
                else {
                    // do dont elt
                    if (doIdx < dos.size() - 1) {
                        ++doIdx;
                    }
                    active = false;
                }
            }
            else if(elts[i].first >= dos[doIdx] && elts[i].first <= donts[dontIdx]) {
                // do elt dont
                if (doIdx < dos.size() - 1) {
                    ++doIdx;
                }
                active = true;
            }
            else if(elts[i].first <= dos[doIdx] && elts[i].first >= donts[dontIdx]) {
                // dont elt do
                if (dontIdx < donts.size() - 1) {
                    ++dontIdx;
                }
                active = false;
            }


            if(active) {
                int x, y;
                char comma;
                std::stringstream ss(elts[i].second);
                ss >> x >> comma >> y;
                mulCount += x * y;
            }
        }
        // calculate the muls
        // for (const auto& elt : elts) {
        //     int x, y;
        //     char comma;
        //     std::stringstream ss(elt.second);
        //     ss >> x >> comma >> y;
        //     mulCount += x * y;
        // }

    }
    std::cout << mulCount << std::endl;

    return 0;
}
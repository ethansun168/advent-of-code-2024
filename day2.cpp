#include <vector>
#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <string>
#include <sstream>

bool part1(const std::vector<int>& vec) {
    if(vec.empty() || vec.size() == 1) {
        return true;
    }

    if (vec[0] < vec[1]) {
        // vec must be increasing
        for (int i = 1; i < vec.size(); ++i) {
            if (vec[i] - vec[i - 1] > 3 || vec[i] - vec[i - 1] < 1) {
                return false;
            }
        }
        return true;
    }
    else {
        // vec must be decreasing
        for (int i = 1; i < vec.size(); ++i) {
            if (vec[i - 1] - vec[i] > 3 || vec[i - 1] - vec[i] < 1) {
                return false;
            }
        }
        return true;
    }

    return false;
}

bool part2(const std::vector<int>& vec) {
    if(vec.size() < 3) {
        return true;
    }

    int remove = 0;
    for (int i = 0; i < vec.size(); ++i) {
        std::vector<int> newVec = vec;
        newVec.erase(newVec.begin() + remove);
        bool flag = true;
        if (newVec[0] < newVec[1]) {
            // vec must be increasing
            for (int i = 1; i < newVec.size(); ++i) {
                if (newVec[i] - newVec[i - 1] > 3 || newVec[i] - newVec[i - 1] < 1) {
                    flag = false;
                    break;
                }
            }
            if (flag) {
                return true;
            }
        }
        else {
            // vec must be decreasing
            for (int i = 1; i < newVec.size(); ++i) {
                if (newVec[i - 1] - newVec[i] > 3 || newVec[i - 1] - newVec[i] < 1) {
                    flag = false;
                    break;
                }
            }
            if (flag) {
                return true;
            }
        }

        ++remove;
    }

    return false;
}

int main(int argc, char** argv) {

    // handle input
    std::string line;
    int count1 = 0;
    int count2 = 0;
    while(getline(std::cin, line)) {
        std::stringstream ss(line);
        int num;
        std::vector<int> l;
        while (ss >> num) {
            l.push_back(num);
        }
        if (part1(l)) {
            ++count1;
        }
        if (part2(l)) {
            ++count2;
        }
    }
    std::cout << "Part 1: " << count1 << std::endl;
    std::cout << "Part 2: " << count2 << std::endl;

    return 0;
}
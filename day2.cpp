#include <vector>
#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <string>
#include <sstream>

bool isSafe(const std::vector<int>& vec) {
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

int main(int argc, char** argv) {

    // handle input
    std::string line;
    int count = 0;
    while(getline(std::cin, line)) {
        std::stringstream ss(line);
        int num;
        std::vector<int> l;
        while (ss >> num) {
            l.push_back(num);
        }
        if (isSafe(l)) {
            ++count;
        }
    }
    std::cout << count << std::endl;


    return 0;
}
#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <sstream>

void increment(std::vector<int>& vec, int index) {
    // base case
    if (index == vec.size()) {
        return;
    }
    if (vec[index] == 0) {
        vec[index] = 1;
        return;
    }
    if (vec[index] == 1) {
        vec[index] = 2;
        return;
    }
    
    // recurse
    vec[index] = 0;
    increment(vec, index + 1);
    return;
}

bool evaluate(long num, const std::vector<long>& vec) {
    // can the ints in vec evaluate to num?
    // 0 means addition, 1 means mult
    std::vector<int> ops(vec.size() - 1, 0);
    int count = 0;
    while (count < std::pow(3, ops.size())) {
        long x = vec[0];
        for (int i = 0; i < ops.size(); ++i) {
            if (ops[i] == 0) {
                // add
                x += vec[i + 1];
            }
            else if(ops[i] == 1) {
                // mult
                x *= vec[i + 1];
            }
            else {
                // concat
                x = std::stol(std::to_string(x) + std::to_string(vec[i + 1]));
            }
        }
        if (num == x) {
            return true;
        }
        increment(ops, 0);
        ++count;
    }
    return false;
}

// void printVec(const std::vector<int>& vec) {
//     for (const auto elt : vec) {
//         std::cout << elt << " ";
//     }
//     std::cout << std::endl;
// }

// int main() {
//     std::vector<int> vec = {0,0,0,0};
//     increment(vec, 0);
//     printVec(vec);

//     vec = {1,0,0,0};
//     increment(vec, 0);
//     printVec(vec);


//     vec = {1,2,0,0};
//     increment(vec, 0);
//     printVec(vec);


//     vec = {2,1,0,0};
//     increment(vec, 0);
//     printVec(vec);


//     vec = {2,2,1,0};
//     increment(vec, 0);
//     printVec(vec);

//     vec = {2,1,2,0};
//     increment(vec, 0);
//     printVec(vec);
// }

int main(int argc, char** argv) {
    // brute force
    long count = 0;
    std::string line;
    while (getline(std::cin, line)) {
        std::stringstream ss(line);
        long num;
        char colon;
        std::vector<long> vec;
        ss >> num >> colon;
        int x;
        while (ss >> x) {
            vec.push_back(x);
        }
        if(evaluate(num, vec)) {
            count += num;
        }
    }
    std::cout << count << std::endl;
}
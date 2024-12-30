#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <sstream>

void incrementBool(std::vector<bool>& vec, int index) {
    // base case
    if (index == vec.size()) {
        return;
    }
    if (vec[index] == 0) {
        vec[index] = 1;
        return;
    }
    // recurse
    vec[index] = 0;
    incrementBool(vec, index + 1);
    return;
}

void incrementInt(std::vector<int>& vec, int index) {
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
    incrementInt(vec, index + 1);
    return;
}

bool part1(long num, const std::vector<long>& vec) {
    // can the ints in vec evaluate to num?
    // 0 means addition, 1 means mult
    std::vector<bool> ops(vec.size() - 1, 0);
    int count = 0;
    while (count < std::pow(2, ops.size())) {
        long x = vec[0];
        for (int i = 0; i < ops.size(); ++i) {
            if (ops[i] == 0) {
                // add
                x += vec[i + 1];
            }
            else {
                // mult
                x *= vec[i + 1];
            }
        }
        if (num == x) {
            return true;
        }
        incrementBool(ops, 0);
        ++count;
    }
    return false;
}

bool part2(long num, const std::vector<long>& vec) {
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
        incrementInt(ops, 0);
        ++count;
    }
    return false;
}

int main(int argc, char** argv) {
    // brute force
    long count1 = 0;
    long count2 = 0;
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
        if(part1(num, vec)) {
            count1 += num;
        }
        if(part2(num, vec)) {
            count2 += num;
        }
    }
    std::cout << "Part 1: " << count1 << std::endl;
    std::cout << "Part 2: " << count2 << std::endl;

}
#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <sstream>

void increment(std::vector<bool>& vec, int index) {
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
    increment(vec, index + 1);
    return;
}

bool evaluate(long num, const std::vector<long>& vec) {
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
        increment(ops, 0);
        ++count;
    }
    return false;
}

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
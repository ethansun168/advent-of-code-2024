#include <vector>
#include <algorithm>
#include <iostream>
#include <unordered_map>

int main(int argc, char** argv) {
    
    int leftNum;
    int rightNum;
    std::vector<int> left;
    std::unordered_map<int, int> right;
    while (std::cin >> leftNum >> rightNum) {
        left.push_back(leftNum);
        // right num goes into hash map
        ++right[rightNum];
    }

    // sort(left.begin(), left.end());
    // sort(right.begin(), right.end());
    int similarity = 0;
    for (int i = 0; i < left.size(); ++i) {
        if (right.find(left[i]) != right.end()) {
            similarity += left[i] * right[left[i]];
        }
    }
    std::cout << similarity << std::endl;

    return 0;
}
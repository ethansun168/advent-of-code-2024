#include <unordered_map>
#include <vector>
#include <algorithm>
#include <iostream>

void part1(const std::vector<int>& left, const std::vector<int>& right) {
    int distance = 0;
    for (int i = 0; i < left.size(); ++i) {
        distance += abs(left[i] - right[i]);
    }
    std::cout << "Part 1: " << distance << std::endl;
}

void part2(const std::vector<int>& left, const std::unordered_map<int, int>& right) {
    int similarity = 0;
    for (int i = 0; i < left.size(); ++i) {
        if (right.find(left[i]) != right.end()) {
            similarity += left[i] * right.find(left[i])->second;
        }
    }
    std::cout << "Part 2: " << similarity << std::endl;
}

int main() {
    int leftNum;
    int rightNum;
    std::vector<int> left;
    std::vector<int> r;
    std::unordered_map<int, int> right;
    while (std::cin >> leftNum >> rightNum) {
        left.push_back(leftNum);
        r.push_back(rightNum);
        // right num goes into hash map
        ++right[rightNum];
    }

    sort(left.begin(), left.end());
    sort(r.begin(), r.end());

    part1(left, r);
    part2(left, right);

    return 0;
}
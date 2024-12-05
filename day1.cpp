#include <vector>
#include <algorithm>
#include <iostream>

int main(int argc, char** argv) {
    
    int leftNum;
    int rightNum;
    std::vector<int> left;
    std::vector<int> right;
    while (std::cin >> leftNum >> rightNum) {
        left.push_back(leftNum);
        right.push_back(rightNum);
    }

    sort(left.begin(), left.end());
    sort(right.begin(), right.end());
    int distance = 0;
    for (int i = 0; i < left.size(); ++i) {
        distance += abs(left[i] - right[i]);
    }
    std::cout << distance << std::endl;

    return 0;
}
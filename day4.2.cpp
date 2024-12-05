#include <vector>
#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <string>
#include <sstream>

// four orientations
// M . M    M . S
// . A .    . A .
// S . S    M . S

// S . M    S . S
// . A .    . A .
// S . M    M . M

// Just check top left corner
bool verify(const std::vector<std::vector<char>>& grid, const int row, const int col) {
    if (
        grid[row][col] == 'M' &&
        grid[row][col + 2] == 'M' &&
        grid[row + 2][col] == 'S' &&
        grid[row + 2][col + 2] == 'S'
    ) {
        return true;
    }

    
    if (
        grid[row][col] == 'M' &&
        grid[row][col + 2] == 'S' &&
        grid[row + 2][col] == 'M' &&
        grid[row + 2][col + 2] == 'S'
    ) {
        return true;
    }

    if (
        grid[row][col] == 'S' &&
        grid[row][col + 2] == 'M' &&
        grid[row + 2][col] == 'S' &&
        grid[row + 2][col + 2] == 'M'
    ) {
        return true;
    }

    if (
        grid[row][col] == 'S' &&
        grid[row][col + 2] == 'S' &&
        grid[row + 2][col] == 'M' &&
        grid[row + 2][col + 2] == 'M'
    ) {
        return true;
    }

    return false;
}

int findXMAS(const std::vector<std::vector<char>>& grid) {
    int count = 0;

    for (int row = 0; row < grid.size() - 2; ++row) {
        for (int col = 0; col < grid[0].size() - 2; ++col) {
            if ((grid[row][col] == 'M' || grid[row][col] == 'S') && grid[row + 1][col + 1] == 'A') {
                if (verify(grid, row, col)) {
                    ++count;
                }
            }
        }
    }

    return count;
}

int main(int argc, char** argv) {
    std::string line;
    std::vector<std::vector<char>> grid;
    while(getline(std::cin, line)) {
        std::vector<char> row;
        std::stringstream ss(line);
        char ch;
        while (ss >> ch) {
            row.push_back(ch);
        }
        grid.push_back(row);
    }
    std::cout << findXMAS(grid) << std::endl;
    return 0;
}
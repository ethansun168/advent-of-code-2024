#include <vector>
#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <string>
#include <sstream>

int numAt(const std::vector<std::vector<char>>& grid, const int row, const int col, const std::string str) {
    int count = 0;
    //forward
    bool flag = true;
    int newCol = col;
    for (int i = 0; i < str.size(); ++i) {
        if (newCol >= grid[0].size() || grid[row][newCol++] != str[i]) {
            flag = false;
            break;
        }
    }
    if (flag) {
        ++count;
    }
    
    // backward
    flag = true;
    newCol = col;
    for (int i = 0; i < str.size(); ++i) {
        if (newCol < 0 || grid[row][newCol--] != str[i]) {
            flag = false;
            break;
        }
    }
    if (flag) {
        ++count;
    }

    // down
    flag = true;
    int newRow = row;
    for (int i = 0; i < str.size(); ++i) {
        if (newRow >= grid.size() || grid[newRow++][col] != str[i]) {
            flag = false;
            break;
        }
    }
    if (flag) {
        ++count;
    }

    // up
    flag = true;
    newRow = row;
    for (int i = 0; i < str.size(); ++i) {
        if (newRow < 0 || grid[newRow--][col] != str[i]) {
            flag = false;
            break;
        }
    }
    if (flag) {
        ++count;
    }

    // diag right down
    flag = true;
    newRow = row;
    newCol = col;
    for (int i = 0; i < str.size(); ++i) {
        if (newRow >= grid.size() || newCol >= grid[0].size() || grid[newRow++][newCol++] != str[i]) {
            flag = false;
            break;
        }
    }
    if (flag) {
        ++count;
    }

    // diag right up
    flag = true;
    newRow = row;
    newCol = col;
    for (int i = 0; i < str.size(); ++i) {
        if (newRow < 0 || newCol >= grid[0].size() || grid[newRow--][newCol++] != str[i]) {
            flag = false;
            break;
        }
    }
    if (flag) {
        ++count;
    }

    // diag left down
    flag = true;
    newRow = row;
    newCol = col;
    for (int i = 0; i < str.size(); ++i) {
        if (newRow >= grid.size() || newCol < 0 || grid[newRow++][newCol--] != str[i]) {
            flag = false;
            break;
        }
    }
    if (flag) {
        ++count;
    }

    // diag left up
    flag = true;
    newRow = row;
    newCol = col;
    for (int i = 0; i < str.size(); ++i) {
        if (newRow < 0 || newCol < 0 || grid[newRow--][newCol--] != str[i]) {
            flag = false;
            break;
        }
    }
    if (flag) {
        ++count;
    }

    return count;
}

int findWord(const std::vector<std::vector<char>>& grid, std::string str) {
    int totalCount = 0;
    for (int row = 0; row < grid.size(); ++row) {
        for (int col = 0; col < grid[0].size(); ++col) {
            if (grid[row][col] == str[0]) {
                totalCount += numAt(grid, row, col, str);
            }
        }
    }

    return totalCount;
}

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
    std::cout << "Part 1: " << findWord(grid, "XMAS") << std::endl;
    std::cout << "Part 2: " << findXMAS(grid) << std::endl;
    return 0;
}
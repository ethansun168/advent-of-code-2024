#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <deque>

struct Point {
    int row;
    int col;
    int val;
};

int countScore(const std::vector<std::vector<int>>& grid, Point p) {
    int score = 0;
    std::deque<Point> search;
    std::vector<std::vector<bool>> visited(grid.size(), std::vector<bool>(grid[0].size(), false));
    search.push_back(p);

    while (!search.empty()) {
        int row = search.front().row;
        int col = search.front().col;
        int val = search.front().val;
        search.pop_front();
        // std::cout << row << " " << col << " " << val << std::endl;
        if (visited[row][col]) {
            continue;
        }
        visited[row][col] = true;

        if (val == 9) {
            score += 1;
            continue;
        }
        
        // left
        if (col + 1 < grid[0].size() && grid[row][col + 1] == val + 1) {
            search.push_back({row, col + 1, val + 1});
        }
        // right
        if (col - 1 >= 0 && grid[row][col - 1] == val + 1) {
            search.push_back({row, col - 1, val + 1});
        }
        // down
        if (row + 1 < grid.size() && grid[row + 1][col] == val + 1) {
            search.push_back({row + 1, col, val + 1});
        }
        // up
        if (row - 1 >= 0 && grid[row - 1][col] == val + 1) {
            search.push_back({row - 1, col, val + 1});
        }

    }


    return score;
}

int main() {
    // Find trailheads
    std::vector<Point> trailheads;
    std::string line;
    std::vector<std::vector<int>> grid;
    int rowNum = 0;
    while (getline(std::cin, line)) {
        std::vector<int> row;
        int col = 0;
        for (const auto& ch : line) {
            if (ch == '.') {
                row.push_back(-1);
            }
            else {
                row.push_back(ch - '0');
            }
            if (ch == '0') {
                Point p = {rowNum, col, 0};
                trailheads.push_back(p);
            }
            ++col;
        }
        grid.push_back(row);
        ++rowNum;
    }

    int score = 0;
    for (const auto& point : trailheads) {
        score += countScore(grid, point); 
    }

    std::cout << score << std::endl;
}
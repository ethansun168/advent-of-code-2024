#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <deque>
#include <utility>

struct Point {
    int row;
    int col;
    char val;
};

struct pair_hash {
    template <typename T1, typename T2>
    std::size_t operator()(const std::pair<T1, T2>& p) const {
        return std::hash<T1>{}(p.first) ^ (std::hash<T2>{}(p.second) << 1);
    }
};

int calcPrice(const std::unordered_map<std::pair<int, int>, bool, pair_hash>& region) {
    int area = region.size();
    // Expand from top left to bottom right
    int sides = 0;
    for (const auto& [point, exist] : region) {
        // Left
        /*
            if left exists, do nothing
            else if top left corner exists, + 1
            else if top does not exist, +1
            else +0
        */

        if (region.find({point.first, point.second - 1}) == region.end()) {
            if (region.find({point.first - 1, point.second - 1}) != region.end()) {
                ++sides;
            }
            else if(region.find({point.first - 1, point.second}) == region.end()) {
                ++sides;
            }
        }

        // Up
        /*
            if up exists, do nothing
            else if top left corner exists, +1
            else if left does not exist, +1
            else +0
        */
        if (region.find({point.first - 1, point.second}) == region.end()) {
            if (region.find({point.first - 1, point.second - 1}) != region.end()) {
                ++sides;
            }
            else if (region.find({point.first, point.second - 1}) == region.end()) {
                ++sides;
            }
        }

        // Right
        /*
            if right exists, do nothing
            else if top right corner exists, +1
            else if up does not exist, +1
            else +0 
        */
        if (region.find({point.first, point.second + 1}) == region.end()) {
            if (region.find({point.first - 1, point.second + 1}) != region.end()) {
                ++sides;
            }
            else if (region.find({point.first - 1, point.second}) == region.end()) {
                ++sides;
            }
        }

        // Down
        /*
            if down exists, do nothing
            else if bottom left corner exists, +1
            else if left does not exist, +1
            else +0 
        */
        if (region.find({point.first + 1, point.second}) == region.end()) {
            if (region.find({point.first + 1, point.second - 1}) != region.end()) {
                ++sides;
            }
            else if (region.find({point.first, point.second - 1}) == region.end()) {
                ++sides;
            }
        }
    }
    return area * sides;
}


int totalPrice(const std::vector<std::vector<char>>& grid) {
    // bfs
    std::vector<std::vector<bool>> visited(grid.size(), std::vector<bool>(grid[0].size(), false));
    int price = 0;
    
    // Every coordinate gets to try, if visited, skip
    for (int r = 0; r < grid.size(); ++r) {
        for (int c = 0; c < grid[0].size(); ++c) {
            if (visited[r][c]) {
                continue;
            }
            char curChar = grid[r][c];

            std::deque<Point> search;
            std::unordered_map<std::pair<int, int>, bool, pair_hash> region;
            search.push_back({r, c, grid[r][c]});
            while (!search.empty()) {
                int row = search.front().row;
                int col = search.front().col;
                char val = search.front().val;
                // std::cout << row << " " << col << " " << val << std::endl;
                search.pop_front();

                if (visited[row][col]) {
                    continue;
                }
                
                if (curChar != val) {
                    continue;
                }

                visited[row][col] = true;
                region[{row, col}] = true;
                
                // left
                if (col + 1 < grid[0].size() && grid[row][col + 1] == curChar) {
                    search.push_back({row, col + 1, curChar});
                }
                // right
                if (col - 1 >= 0 && grid[row][col - 1] == curChar) {
                    search.push_back({row, col - 1, curChar});
                }
                // down
                if (row + 1 < grid.size() && grid[row + 1][col] == curChar) {
                    search.push_back({row + 1, col, curChar});
                }
                // up
                if (row - 1 >= 0 && grid[row - 1][col] == curChar) {
                    search.push_back({row - 1, col, curChar});
                }
            }
            price += calcPrice(region);
        }
    }
    return price;
}

void printGrid(const std::vector<std::vector<char>>& grid) {
    for (const auto& row : grid) {
        for (const auto ch : row) {
            std::cout << ch << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

int main() {
    std::string line;
    std::vector<std::vector<char>> grid;
    while (getline(std::cin, line)) {
        std::vector<char> row;
        for (const auto& ch : line) {
            row.push_back(ch);
        }
        grid.push_back(row);
    }

    // printGrid(grid);

    std::cout << totalPrice(grid) << std::endl;
}
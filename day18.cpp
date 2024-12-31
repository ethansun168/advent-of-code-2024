#include <cmath>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <deque>
#include <queue>
#include <functional>

const int GRID_SIZE = 71;
const int EXAMPLE_SIZE = 7;
const int EXAMPLE_STEP = 12;
const int KILOBYTE = 1024;

class Grid {
private:
    int gridSize;
    std::vector<std::vector<char>> grid;
    std::vector<std::vector<char>> backtrace;
public:
    
    Grid(int gSize) {
        gridSize = gSize;
        grid.resize(gridSize, std::vector<char>(gridSize, '.'));
        backtrace.resize(grid.size(), std::vector<char>(grid[0].size(), '.')); 
    }

    std::pair<int, int> corrupt(int step) {
        int col, row;
        for (int i = 0; i < step; ++i) {
            char ch;
            std::cin >> col >> ch >> row;
            grid[row][col] = '#';
        }
        return {col, row};
    } 

    void printBacktrace() {
        for (const auto& r : backtrace) {
            for (const auto& ch : r) {
                std::cout << ch;
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }

    void print() const {
        for (const auto& r : grid) {
            for (const auto& ch : r) {
                std::cout << ch;
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }

    void solve() {
        int row = 0;
        int col = 0;
        std::vector<std::vector<bool>> visited(grid.size(), std::vector<bool>(grid[0].size(), false));
        std::deque<std::pair<int, int>> search;
        
        search.push_back({0, 0});

        while (!search.empty()) {
            row = search.front().first;
            col = search.front().second;
            search.pop_front();
            if (visited[row][col]) {
                continue;
            }
            visited[row][col] = true;
            if (row == gridSize - 1 && col == gridSize - 1) {
                break;
            }
            
            // up
            if (row > 0 && grid[row - 1][col] != '#' && !visited[row - 1][col]) {
                backtrace[row - 1][col] = 'v';
                search.push_back({row - 1, col});
            }
            // down
            if (row < grid.size() - 1 && grid[row + 1][col] != '#' && !visited[row + 1][col]) {
                backtrace[row + 1][col] = '^';
                search.push_back({row + 1, col});
            }
            // left
            if (col > 0 && grid[row][col - 1] != '#' && !visited[row][col - 1]) {
                backtrace[row][col - 1] = '>';
                search.push_back({row, col - 1});
            }
            // right
            if (col < grid[0].size() - 1 && grid[row][col + 1] != '#' && !visited[row][col + 1]) {
                backtrace[row][col + 1] = '<';
                search.push_back({row, col + 1});
            }
        }
    }

    int countBacktrace() const {
        int row = gridSize - 1;
        int col = gridSize - 1;
        int count = 0;
        while (row != 0 || col != 0) {
            ++count;
            char direction = backtrace[row][col];
            switch (direction) {
                case '^': {
                    --row;
                    break;
                }
                case 'v': {
                    ++row;
                    break;
                }
                case '<': {
                    --col;
                    break;
                }
                case '>': {
                    ++col;
                    break;
                }

            }
        }
        return count;
    }

    std::pair<int, int> part2() {
        while (true) {
            std::pair<int, int> coord = corrupt(1);
            backtrace.clear();
            backtrace.resize(grid.size(), std::vector<char>(grid[0].size(), '.')); 
            solve();
            if (backtrace[gridSize - 1][gridSize - 1] == '.') {
                return coord;
            }
        }
    }

};

int main() {
    // Use this for the example
    // Grid grid(EXAMPLE_SIZE);
    // grid.corrupt(EXAMPLE_STEP);
    // grid.solve();

    Grid grid(GRID_SIZE);
    grid.corrupt(KILOBYTE);
    grid.solve();
    std::cout << "Part 1: " << grid.countBacktrace() << std::endl;
    std::pair<int, int> ans = grid.part2();
    std::cout << "Part 2: " << ans.first << "," << ans.second << std::endl;
}
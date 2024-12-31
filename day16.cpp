#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <deque>
#include <queue>
#include <functional>

class Grid {
private:
    enum class Direction {
        North,
        South,
        East,
        West
    };
    std::vector<std::vector<char>> grid;
    std::vector<std::vector<char>> backtrace;
    std::pair<int, int> start;
    std::pair<int, int> end;

public:
    Grid() {}

    void print() {
        for (const auto& r : grid) {
            for (const auto& ch : r) {
                std::cout << ch;
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }

    void fillGrid() {
        std::string line;
        int r = 0;
        while (getline(std::cin, line)) {
            int c = 0;
            std::vector<char> row;
            for (const auto& ch : line) {
                if (ch == 'S') {
                    start = {r, c};
                } else if (ch == 'E') {
                    end = {r, c};
                }
                row.push_back(ch);
                ++c;
            }
            grid.push_back(row);
            backtrace.push_back(row);
            ++r;
        }
    }

};

int main() {
    Grid grid;
    grid.fillGrid();
    grid.print();
}
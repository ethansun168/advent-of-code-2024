#include <iostream>
#include <string>
#include <sstream>
#include <vector>

bool done(const std::vector<std::vector<char>>& map, int curRow, int curCol) {
    // curRow curCol must be on thet edge and facing outward
    if (curRow == 0 && map[curRow][curCol] == '^') {
        return true;
    }
    if (curRow == map.size() - 1 && map[curRow][curCol] == 'V') {
        return true;
    }
    if (curCol == 0 && map[curRow][curCol] == '<') {
        return true;
    }
    if (curCol == map[0].size() - 1 && map[curRow][curCol] == '>') {
        return true;
    }

    return false;
}

void printMap(const std::vector<std::vector<char>>& map) {
    for (const auto& row : map) {
        for (const auto& ch : row) {
            std::cout << ch << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

void simulate(std::vector<std::vector<char>>& map, int startRow, int startCol) {
    // Fill path with X
    int curRow = startRow;
    int curCol = startCol;
    while (!done(map, curRow, curCol)) {
        if (map[curRow][curCol] == '^') {
            // up
            if (map[curRow - 1][curCol] == '#') {
                // turn right
                map[curRow][curCol] = '>';
            }
            else {
                map[curRow][curCol] = 'X';
                --curRow;
                map[curRow][curCol] = '^';
            }
        }
        else if (map[curRow][curCol] == '>') {
            // right
            if (map[curRow][curCol + 1] == '#') {
                map[curRow][curCol] = 'V';
            }
            else {
                map[curRow][curCol] = 'X';
                ++curCol;
                map[curRow][curCol] = '>';
            }
        }
        else if (map[curRow][curCol] == '<') {
            // left
            if (map[curRow][curCol - 1] == '#') {
                map[curRow][curCol] = '^';
            }
            else {
                map[curRow][curCol] = 'X';
                --curCol;
                map[curRow][curCol] = '<';
            }
        }
        else if (map[curRow][curCol] == 'V') {
            // down
            if (map[curRow + 1][curCol] == '#') {
                map[curRow][curCol] = '<';
            }
            else {
                map[curRow][curCol] = 'X';
                ++curRow;
                map[curRow][curCol] = 'V';
            }
        }
        // printMap(map);
    }
    map[curRow][curCol] = 'X';
    // printMap(map);
}

int main(int argc, char** argv) {
    std::vector<std::vector<char>> map;
    std::string line;
    int startRow = 0, startCol = 0;
    int row = 0;
    while(getline(std::cin, line)) {
        int col = 0;
        std::stringstream ss(line);
        std::vector<char> r;
        char ch;
        while (ss >> ch) {
            if (ch == '^') {
                startRow = row;
                startCol = col;
            }
            r.push_back(ch);
            ++col;
        }
        map.push_back(r);
        ++row;
    }
    simulate(map, startRow, startCol);
    // Count X's
    int count = 0;
    for (const auto& r : map) {
        for (const auto& ch : r) {
            if (ch == 'X') {
                ++count;
            }
        }
    }
    std::cout << count << std::endl;

}
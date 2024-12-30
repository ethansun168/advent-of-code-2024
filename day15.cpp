#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <deque>
#include <queue>
#include <functional>

enum class Type {
    Empty,
    Box,
    Wall,
    Robot,
    LeftBox,
    RightBox
};

enum class Move {
    Up,
    Down,
    Left,
    Right
};

struct pair_hash {
    template <typename T1, typename T2>
    std::size_t operator()(const std::pair<T1, T2>& p) const {
        return std::hash<T1>{}(p.first) ^ (std::hash<T2>{}(p.second) << 1);
    }
};

std::pair<int, int> left(std::pair<int, int> location) {
    return {location.first, location.second - 1};
}

std::pair<int, int> right(std::pair<int, int> location) {
    return {location.first, location.second + 1};
}

std::pair<int, int> up(std::pair<int, int> location) {
    return {location.first - 1, location.second};
}

std::pair<int, int> down(std::pair<int, int> location) {
    return {location.first + 1, location.second};
}

void printGrid(const std::unordered_map<std::pair<int, int>, Type, pair_hash>& grid, int row, int col) {
    std::vector<std::vector<char>> g(row, std::vector<char>(col, '.'));
    for (const auto& [coord, type] : grid) {
        switch (type) {
            case Type::Empty:
                g[coord.first][coord.second] = '.';
                break;
            case Type::Box:
                g[coord.first][coord.second] = 'O';
                break;
            case Type::Wall:
                g[coord.first][coord.second] = '#';
                break;
            case Type::Robot:
                g[coord.first][coord.second] = '@';
                break;
            case Type::LeftBox:
                g[coord.first][coord.second] = '[';
                break;
            case Type::RightBox:
                g[coord.first][coord.second] = ']';
                break;
        }
    }

    for (const auto& row : g) {
        for (const auto& ch : row) {
            std::cout << ch; 
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

int totalGPS(const std::unordered_map<std::pair<int, int>, Type, pair_hash>& grid) {
    int gps = 0;
    for (const auto& [coord, type] : grid) {
        if (type == Type::Box) {
            gps += 100 * coord.first + coord.second;
        }
    }
    return gps;
}

void moveBoxesHelper(std::unordered_map<std::pair<int, int>, Type, pair_hash>& grid, std::pair<int, int>& location, std::function<std::pair<int, int>(std::pair<int, int>)> dir) {
    std::pair<int, int> scan = dir(location);
    bool move = false;
    while (grid[scan] != Type::Wall) {
        if (grid[scan] == Type::Empty) {
            move = true;
            break;
        }
        scan = dir(scan); 
    } 
    if (move) {
        // Move box left of robot to scan, move robot to left
        grid[scan] = Type::Box;
        grid[location] = Type::Empty;
        location = dir(location);
        grid[location] = Type::Robot;
    }
}

void moveBoxes(std::unordered_map<std::pair<int, int>, Type, pair_hash> grid, const std::vector<Move>& moves, std::pair<int, int> start) {
    std::pair<int, int> location = start;
    for (const auto& move : moves) {
        switch(move) {
            case Move::Left: {
                moveBoxesHelper(grid, location, left);
                break;
            }
            case Move::Right: {
                moveBoxesHelper(grid, location, right);
                break;
            }
            case Move::Up: {
                moveBoxesHelper(grid, location, up);
                break;
            }
            case Move::Down: {
                moveBoxesHelper(grid, location, down);
                break;
            }
        }
    }

    std::cout << "Part 1: " << totalGPS(grid) << std::endl;
}

bool compareUpPair(const std::pair<int, int>& a, const std::pair<int, int>& b) {
    if (a.first == b.first) {
        return a.second > b.second;
    }
    return a.first > b.first;
}

bool compareDownPair(const std::pair<int, int>& a, const std::pair<int, int>& b) {
    if (a.first == b.first) {
        return a.second < b.second;
    }
    return a.first < b.first;
}

void lrHelper(
    std::unordered_map<std::pair<int, int>, Type, pair_hash>& grid,
    std::pair<int, int>& location,
    std::function<std::pair<int, int>(std::pair<int, int>)> dir1,
    std::function<std::pair<int, int>(std::pair<int, int>)> dir2
) {

    std::pair<int, int> scan = dir1(location);
    bool move = false;
    while (grid[scan] != Type::Wall) {
        if (grid[scan] == Type::Empty) {
            move = true;
            break;
        }
        scan = dir1(scan);
    }
    if (move) {
        // Move from scan to location
        while (scan != location) {
            grid[scan] = grid[dir2(scan)];
            scan = dir2(scan);
        }
        grid[location] = Type::Empty;
        location = dir1(location);
        grid[location] = Type::Robot;
    }

}

void udHelper(
    std::unordered_map<std::pair<int, int>, Type, pair_hash>& grid,
    std::pair<int, int>& location,
    std::function<std::pair<int, int>(std::pair<int, int>)> dir,
    std::function<bool(const std::pair<int, int>&, const std::pair<int, int>&)> comp
) {
    auto comparator = [&comp](const std::pair<int, int>& a, const std::pair<int, int>& b) {
        return comp(a, b);
    };

    std::deque<std::pair<int, int>> search;
    search.push_back(dir(location));
    if (grid[dir(location)] == Type::LeftBox) {
        search.push_back(right(dir(location)));
    }
    else if (grid[dir(location)] == Type::RightBox){
        search.push_back(left(dir(location)));
    }
    
    bool move = true;
    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, decltype(comparator)> boxesToMove(comparator);
    std::unordered_map<std::pair<int, int>, bool, pair_hash> visited;
    while (!search.empty()) {
        std::pair<int, int> scan = search.front();
        search.pop_front();
        if (visited[scan]) {
            continue;
        }
        visited[scan] = true;
        if (grid[scan] == Type::Empty) {
            continue;
        }
        if (grid[scan] == Type::Wall) {
            move = false;
            break;
        }
        boxesToMove.push(scan);

        // If different than current tile, add left/right to search as well
        search.push_back(dir(scan));
        if (grid[scan] != grid[dir(scan)] && grid[dir(scan)] != Type::Wall && grid[dir(scan)] != Type::Empty) {
            if (grid[dir(scan)] == Type::LeftBox) {
                search.push_back(right(dir(scan)));
            }
            else {
                search.push_back(left(dir(scan)));
            }
        }
    }
    if (move) {
        while (!boxesToMove.empty()) {
            std::pair<int, int> box = boxesToMove.top();
            grid[dir(box)] = grid[box];
            grid[box] = Type::Empty;
            // std::cout << box.first << " " << box.second << std::endl; 
            boxesToMove.pop();
        }
        grid[location] = Type::Empty;
        location = dir(location);
        grid[location] = Type::Robot;
    }
}

int totalExpandedGPS(const std::unordered_map<std::pair<int, int>, Type, pair_hash>& grid) {
    int gps = 0;
    for (const auto& [coord, type] : grid) {
        if (type == Type::LeftBox) {
            gps += 100 * coord.first + coord.second;
        }
    }
    return gps;
}

void moveExpandedBoxes(std::unordered_map<std::pair<int, int>, Type, pair_hash>& grid, const std::vector<Move>& moves, std::pair<int, int> start) {
    std::pair<int, int> location = start;
    // Left and right is normal
    for (const auto& move : moves) {
        // printGrid(grid, row, col);
        switch(move) {
            case Move::Left: {
                lrHelper(grid, location, left, right);
                break;
            }
            case Move::Right: {
                lrHelper(grid, location, right, left);
                break;
            }
            case Move::Up: {
                udHelper(grid, location, up, compareUpPair);
                break;
            }
            case Move::Down: {
                udHelper(grid, location, down, compareDownPair);
                break;
            }
        }
    }
}

std::pair<int, int> expandCoord(std::pair<int, int> coord) {
    return {coord.first, 2 * coord.second};
}

std::unordered_map<std::pair<int, int>, Type, pair_hash> expandGrid(const std::unordered_map<std::pair<int, int>, Type, pair_hash>& grid) {
    std::unordered_map<std::pair<int, int>, Type, pair_hash> ret;

    for (const auto& [coord, type] : grid) {
        switch (type) {
            case Type::Wall:
                ret[expandCoord(coord)] = Type::Wall;
                ret[right(expandCoord(coord))] = Type::Wall;
                break;
            case Type::Box:
                ret[expandCoord(coord)] = Type::LeftBox;
                ret[right(expandCoord(coord))] = Type::RightBox;
                break;
            case Type::Empty:
                ret[expandCoord(coord)] = Type::Empty;
                ret[right(expandCoord(coord))] = Type::Empty;
                break;
            case Type::Robot:
                ret[expandCoord(coord)] = Type::Robot;
                ret[right(expandCoord(coord))] = Type::Empty;
                break;
        }
    }

    return ret;
}

int main() {
    std::unordered_map<std::pair<int, int>, Type, pair_hash> grid;
    std::string line;
    int row = 0;
    int col = 0;
    std::pair<int, int> start;
    while (getline(std::cin, line)) {
        if (line.empty()) {
            break;
        }
        col = 0;
        for (const auto& ch : line) {
            if (ch == '#') {
                grid[{row, col}] = Type::Wall;
            }
            else if (ch == 'O') {
                grid[{row, col}] = Type::Box;
            }
            else if (ch == '@') {
                start = {row, col};
                grid[{row, col}] = Type::Robot;
            }
            else {
                grid[{row, col}] = Type::Empty;
            }
            ++col;
        }
        ++row;
    }

    std::vector<Move> moves;
    char move;
    while (std::cin >> move) {
        switch (move) {
            case '^':
                moves.push_back(Move::Up);
                break;
            case '<':
                moves.push_back(Move::Left);
                break;
            case '>':
                moves.push_back(Move::Right);
                break;
            case 'v':
                moves.push_back(Move::Down);
                break;
        }
    }

    moveBoxes(grid, moves, start);
    std::unordered_map<std::pair<int, int>, Type, pair_hash> expandedGrid = expandGrid(grid);
    moveExpandedBoxes(expandedGrid, moves, expandCoord(start));
    std::cout << "Part 2: " << totalExpandedGPS(expandedGrid) << std::endl;

    return 0;
}
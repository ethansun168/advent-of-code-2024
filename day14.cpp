#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <unordered_map>

const int NUM_COLS = 101;
const int NUM_ROWS = 103;
const int EXAMPLE_COLS = 11;
const int EXAMPLE_ROWS = 7;
const int NUM_SECONDS = 100;

struct Robot {
    int x;
    int y;
    int vx;
    int vy;
};

void printRobots(const std::vector<Robot>& robots, int numRows, int numCols) {
    std::vector<std::vector<int>> grid(numRows, std::vector<int>(numCols, 0));

    for (const auto& r : robots) {
        ++grid[r.y][r.x];
    }

    std::cout << std::endl;
    for (const auto& row : grid) {
        for (const auto& i : row) {
            if (i == 0) {
                std::cout << ".";
            }
            else {
                std::cout << i;
            }
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

int safetyFactor(const std::vector<Robot>& robots, int numRows, int numCols) {

    int midRow = numRows / 2;
    int midCol = numCols / 2;

    int q1 = 0, q2 = 0, q3 = 0, q4 = 0;

    for (auto& r : robots) {
        if (r.x < midCol && r.y < midRow) {
            ++q1;
        }
        else if (r.x > midCol && r.y < midRow) {
            ++q2;
        }
        else if (r.x < midCol && r.y > midRow) {
            ++q3;
        }
        else if (r.x > midCol && r.y > midRow) {
            ++q4;
        }
    }

    return q1 * q2 * q3 * q4;
}

void increment(std::vector<Robot>& robots, int numSeconds, int numRows, int numCols) {
    for (int i = 0; i < NUM_SECONDS; ++i) {
        for (auto& r : robots) {
            // Teleport based on their velocities
            r.x = (r.x + r.vx + numCols) % numCols;
            r.y = (r.y + r.vy + numRows) % numRows;
        }
    }
}

int main() {
    std::vector<Robot> robots;
    Robot robot;
    char ch;
    while (std::cin >> ch >> ch >> robot.x >> ch >> robot.y >> ch >> ch >> robot.vx >> ch >> robot.vy) {
        robots.push_back(robot);
    }

    bool example = robots.size() == 12;
    int numRows = !example ? NUM_ROWS : EXAMPLE_ROWS;
    int numCols = !example ? NUM_COLS : EXAMPLE_COLS;

    increment(robots, NUM_SECONDS, numRows, numCols);
    int seconds = NUM_SECONDS;

    std::cout << "Part 1: " << safetyFactor(robots, numRows, numCols) << std::endl;

    // part 2 no work?

    int minSafety = __INT_MAX__;
    int minSeconds = 0;
    int upper = 10000;

    for (int i = 0; i < upper; ++i) {
        increment(robots, 1, numRows, numCols);
        ++seconds;
        int x = safetyFactor(robots, numRows, numCols);
        if (x < minSafety) {
            minSafety = x;
            minSeconds = seconds;
            std::cout << "Seconds: " << seconds << std::endl;
            std::cout << "Safety: " << minSafety << std::endl;
            printRobots(robots, numRows, numCols);
        }
    }

    std::cout << "Part 2: " << minSeconds << std::endl;
}
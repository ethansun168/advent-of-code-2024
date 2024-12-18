#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <sstream>
#include <set>

bool inMap(const std::pair<int, int>& coord, int rowSize, int colSize) {
    // filter out antinodes that are off the map < 0 or > rowSize, > colSize
    if (coord.first < 0 || coord.first > rowSize) {
        return false;
    }

    if (coord.second < 0 || coord.second > colSize) {
        return false;
    }

    return true;
}

void antinode(std::set<std::pair<int, int>>& antinodes, std::pair<int, int> one, std::pair<int, int> two, int rowSize, int colSize) {
    // each pair of antennas produce two antinodes
    // (3,4) (5,5)
    // 2 - 1 --> (2, 1)
    // one - diff --> (1, 3)
    // two + diff --> (7, 6)
    std::pair<int, int> diff = {two.first - one.first, two.second - one.second};
    std::pair<int, int> node1 = {one.first - diff.first, one.second - diff.second};
    std::pair<int, int> node2 = {two.first + diff.first, two.second + diff.second};
    // std::pair<int, int> diff = {one.first - two.first, one.second - two.second};
    // std::pair<int, int> node1 = {one.first + diff.first, one.second + diff.second};
    // std::pair<int, int> node2 = {two.first - diff.first, two.second - diff.second};
    
    if (inMap(node1, rowSize, colSize)) {
        antinodes.insert(node1);
    }

    if (inMap(node2, rowSize, colSize)) {
        antinodes.insert(node2);
    }
}

std::set<std::pair<int, int>> findAntinodes(const std::unordered_map<char, std::vector<std::pair<int, int>>>& antennas, int rowSize, int colSize) {
    std::set<std::pair<int, int>> antinodes;
    for (const auto& [key, coords] : antennas) {
        for(int i = 0; i < coords.size() - 1; ++i) {
            for (int j = i + 1; j < coords.size(); ++j) {
                antinode(antinodes, coords[i], coords[j], rowSize, colSize);
            }
        }
    }

    return antinodes;
}


int main(int argc, char** argv) {
    // char to list of coords

    std::unordered_map<char, std::vector<std::pair<int, int>>> antennas;
    std::string line;
    int row = 0;
    int col = 0;
    while (getline(std::cin, line)) {
        col = 0;
        std::stringstream ss(line);
        char ch;
        while (ss >> ch) {
            if (ch != '.') {
                antennas[ch].push_back(std::make_pair(row, col));
            }
            ++col;
        }
        ++row;
    }
    
    std::set<std::pair<int, int>> antinodes = findAntinodes(antennas, row, col);
    std::cout << antinodes.size() << std::endl;
}
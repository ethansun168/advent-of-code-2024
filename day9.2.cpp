#include <algorithm>
#include <unordered_map>
#include <map>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <queue>
#include <ranges>

// This is wrong but idk why

void moveFiles(
    std::map<int, std::pair<int, int>>& fileInfo,
    std::map<int, int> freeIndices
) {
    // move files from greatest id
    for (auto it = fileInfo.rbegin(); it != fileInfo.rend(); ++it) {
        auto [id, pair] = *it;
        auto [index, length] = pair;

        // loop through free indices
        for (auto& [freeIndex, freeLength] : freeIndices) {
            if (freeIndex > index) {
                break;
            }

            if(freeLength >= length) {
                // move the file
                fileInfo[id] = {freeIndex, length};
                // index = freeIndex;
                
                // update freeIndices
                if (freeLength != length) {
                    freeIndices[freeIndex + length] = freeLength - length;
                }
                freeIndices.erase(freeIndex);
                break;
            }
        }
    }
}

long checksum(const std::map<int, std::pair<int, int>>& fileInfo) {
    long sum = 0;
    for (const auto& [id, pair] : fileInfo) {
        auto [index, length] = pair;
        sum += id * (index * length + (length * (length - 1)) / 2);
    }
    return sum;
}

void printFiles(const std::map<int, std::pair<int, int>>& fileInfo) {

    int maxIndex = 0;
    int l = 0;
    for (const auto& [id, pair] : fileInfo) {
        auto [index, length] = pair;
        if (maxIndex < index) {
            maxIndex = index;
            l = length;
        }
    }
    std::string str(maxIndex + l, '.');

    for (const auto& [id, pair] : fileInfo) {
        auto [index, length] = pair;
        for (int i = 0; i < length; ++i) {
            str[index + i] = id + '0';
        }
    }
    std::cout << str << std::endl;
}

int main() {
    int id = 0;
    
    // index --> length of free block
    std::map<int, int> freeIndices;

    // id --> pair<index, length>
    std::map<int, std::pair<int, int>> fileInfo;

    std::string line;
    getline(std::cin, line);

    int index = 0;
    for (int i = 0; i < line.size() - 1; i += 2) {
        int file = line[i] - '0';
        int free = line[i + 1] - '0'; 

        fileInfo[id] = {index, file};
        index += file;
        freeIndices[index] = free;
        index += free;
        ++id;
    }

    if (line.size() % 2) {
        fileInfo[id] = {index, line[line.size() - 1] - '0'};
    }

    printFiles(fileInfo);
    moveFiles(fileInfo, freeIndices);
    printFiles(fileInfo);
    std::cout << checksum(fileInfo) << std::endl;
    return 0;
}


/*
12345
0..111....22222
0*0 + 1*3 + 1*4 + 1*5 + 2*10 + 2*11 + 2*12 + 2*13 + 2*14 = 132

54321
00000....111..2
000002111
0 + 2*5 + 1*6 + 1*7 + 1*8 = 31



*/
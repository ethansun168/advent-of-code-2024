#include <iostream>
#include <string>
#include <sstream>
#include <vector>

int findNextFree(const std::vector<int>& filesystem, int index) {
    for (int i = index; i < filesystem.size(); ++i) {
        if (filesystem[i] == -1) {
            return i;
        }
    }
    return -1;
}

void moveFileBlocks(std::vector<int>& filesystem) {
    int freeIndex = findNextFree(filesystem, 0);
    int prevI = filesystem.size() - 1;

    // loop backwards
    for (int i = filesystem.size() - 1; i >= 0; --i) {
        if (filesystem[i] == -1) {
            continue;
        }
        if (freeIndex > i) {
            filesystem.resize(prevI);
            return;
        }
        filesystem[freeIndex] = filesystem[i];
        
        prevI = i;
        freeIndex = findNextFree(filesystem, freeIndex);
    }
}

long checksum(const std::vector<int>& filesystem) {
    long sum = 0;
    for (int i = 0; i < filesystem.size(); ++i) {
        sum += i * filesystem[i];
    }
    return sum;
}

int main() {
    int id = 0;
    
    std::vector<int> filesystem;
    std::string line;
    getline(std::cin, line);

    for (int i = 0; i < line.size() - 1; i += 2) {
        int file = line[i] - '0';
        int free = line[i + 1] - '0'; 
        for (int i = 0; i < file; ++i) {
            filesystem.push_back(id);
        }

        for (int i = 0; i < free; ++i) {
            filesystem.push_back(-1);
        }
        ++id;
    }
    if (line.size() % 2) {
        for (int i = 0; i < line[line.size() - 1] - '0'; ++i)
        {
            filesystem.push_back(id);
        }
    }

    moveFileBlocks(filesystem);
    std::cout << checksum(filesystem) << std::endl;
    return 0;
}
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <deque>
#include <list>

const int NUM_BLINKS = 25;

std::pair<long, long> split(long num) {
    // num is even length
    std::string numStr = std::to_string(num);
    size_t mid = numStr.size() / 2;
    std::string firstHalf = numStr.substr(0, mid);
    std::string secondHalf = numStr.substr(mid);
    return {std::stol(firstHalf), std::stol(secondHalf)};
}

/*
If the stone is engraved with the number 0, it is replaced by a stone engraved with the number 1.

If the stone is engraved with a number that has an even number of digits, it is replaced by two stones.
    The left half of the digits are engraved on the new left stone, and the right half of the digits are engraved
    on the new right stone. (The new numbers don't keep extra leading zeroes: 1000 would become stones 10 and 0.)

If none of the other rules apply, the stone is replaced by a new stone;
    the old stone's number multiplied by 2024 is engraved on the new stone.
*/
void updateStones(std::list<long>& stones) {
    for (auto it = stones.begin(); it != stones.end(); ++it) {
        if (*it == 0) {
            *it = 1;
        }
        else if (std::to_string(*it).size() % 2 == 0) {
            std::pair<long, long> p = split(*it);
            *it = p.first;
            it = stones.insert(std::next(it), p.second);
        }
        else {
            *it *= 2024;
        }
    }
}

int main() {
    std::list<long> stones;

    long num;
    while (std::cin >> num) {
        stones.push_back(num);
    }

    for (int i = 0; i < NUM_BLINKS; ++i) {
        updateStones(stones);
    }

    std::cout << stones.size() << std::endl;

    return 0;
}
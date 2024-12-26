#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <unordered_map>

struct Machine {
    long xa;
    long xb;
    long ya;
    long yb;
    long x;
    long y;
};

long countTokens(const Machine& m) {
    long det = m.xa * m.yb - m.xb * m.ya;
    if (!det) {
        return 0;
    }

    long a = m.x * m.yb - m.y * m.xb;
    long b = m.y * m.xa - m.x * m.ya;
    if (a % det != 0 || b % det != 0) {
        return 0;
    }
    long B = b / det;
    long A = a / det;
    return 3 * A + B;

    return 3 * A + B;
}

int main() {
    std::string line;
    std::vector<Machine> machines;
    while (getline(std::cin, line)) {
        std::stringstream ss(line);
        Machine machine;
        // A
        std::string str;
        char ch;
        ss >> str >> str >> ch >> ch >> machine.xa >> ch >> ch >> ch >> machine.ya;

        // B
        getline(std::cin, line);
        ss.str("");
        ss.clear();
        ss << line;
        ss >> str >> str >> ch >> ch >> machine.xb >> ch >> ch >> ch >> machine.yb;

        // Prize
        getline(std::cin, line);
        ss.str("");
        ss.clear();
        ss << line;
        ss >> str >> ch >> ch >> machine.x >> ch >> ch >> ch >> machine.y;

        // Blank
        getline(std::cin, line);
        machines.push_back(machine);
    }
    long tokens = 0;
    for (const auto& machine : machines) {
        tokens += countTokens(machine);
    }
    std::cout << "Part 1: " << tokens << std::endl;

    tokens = 0;
    for (auto& machine : machines) {
        machine.x += 10000000000000;
        machine.y += 10000000000000;
        tokens += countTokens(machine);
    }
    std::cout << "Part 2: " << tokens << std::endl;
}
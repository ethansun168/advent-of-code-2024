#include <cmath>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <deque>
#include <queue>
#include <functional>

class Computer {
private:
    int regA;
    int regB;
    int regC;
    int pc;
    std::vector<int> program;
    std::vector<int> out;
public:
    Computer() {
        pc = 0;
    }

    void initRegisters() {
        std::string str;
        int a, b, c;
        char ch;
        std::cin >> str >> str >> a >> str >> str >> b >> str >> str >> c;
        regA = a;
        regB = b;
        regC = c;
    }

    void initProgram() {
        std::string str;
        char ch;
        int a;
        std::cin >> str >> a;
        program.push_back(a);
        while (std::cin >> ch >> a) {
            program.push_back(a);
        }
    }

    void run() {
        while (pc < program.size()) {
            int opcode = program[pc];
            int operand = program[pc + 1];
            int comboOperand = operand;
            if (comboOperand == 4) {
                comboOperand = regA;
            }
            else if (comboOperand == 5) {
                comboOperand = regB;
            }
            else if (comboOperand == 6) {
                comboOperand = regC;
            }
            switch (opcode) {
                case 0: {
                    regA /= pow(2, comboOperand);
                    break;
                }
                case 1: {
                    regB ^= operand;
                    break;
                }
                case 2: {
                    regB = comboOperand % 8;
                    break;
                }
                case 3: {
                    if (regA != 0) {
                        pc = operand;
                        continue;
                    }
                    break;
                }
                case 4: {
                    regB ^= regC;
                    break;
                }
                case 5: {
                    out.push_back(comboOperand % 8);
                    break;
                }
                case 6: {
                    regB = regA / pow(2, comboOperand);
                    break;
                }
                case 7: {
                    regC = regA / pow(2, comboOperand);
                    break;
                }
            }

            pc += 2;
        }
    }
    
    void print() {
        std::cout << out[0];
        for (int i = 1; i < out.size(); ++i) {
            std::cout << "," << out[i];
        }
        std::cout << std::endl;
    }

    void setRegs(int a, int b, int c) {
        regA = a;
        regB = b;
        regC = c;
    }

    void reset() {
        regA = 0;
        regB = 0;
        regC = 0;
        out.clear();
        pc = 0;
    }

    bool runEqual() {
        bool b = program == out;
        return b;
    }

};

/*
    Disassembly

    B = A % 8
    B = B xor 3
    C = A / (2 ^ B)
    A = A / (2 ^ 3)
    B = B xor C
    B = B xor 5
    print(B % 8)
    if A not 0, jump to beginning

*/

int main() {
    Computer pc;
    pc.initRegisters();
    pc.initProgram();
    pc.run();
    std::cout << "Part 1: ";
    pc.print();

    return 0;
}


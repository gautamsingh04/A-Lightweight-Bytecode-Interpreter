#include <iostream>
#include <vector>
#include <cctype>

// Define bytecode instructions
enum OpCode { PUSH, ADD, SUB, PRINT };

// Structure for bytecode instructions
struct Instruction {
    OpCode opcode;
    int value;
};

// Custom string comparison function
bool isEqual(const char* str1, const char* str2) {
    while (*str1 && *str2) {
        if (*str1 != *str2) return false;
        str1++;
        str2++;
    }
    return *str1 == *str2;
}

// Custom function to check if a character is a digit
bool isDigit(char c) {
    return c >= '0' && c <= '9';
}

// Custom function to convert string to integer
int toInt(const char* str) {
    int num = 0;
    while (*str) {
        if (!isDigit(*str)) return 0;
        num = num * 10 + (*str - '0');
        str++;
    }
    return num;
}

// Tokenizer (Lexer)
std::vector<std::string> tokenize(const std::string &code) {
    std::vector<std::string> tokens;
    std::string token = "";
    for (size_t i = 0; i < code.size(); ++i) {
        if (code[i] == ' ') {
            if (!token.empty()) {
                tokens.push_back(token);
                token = "";
            }
        } else {
            token += code[i];
        }
    }
    if (!token.empty()) tokens.push_back(token);
    return tokens;
}

// Simple Parser + Bytecode Generator
std::vector<Instruction> parseAndGenerateBytecode(const std::vector<std::string> &tokens) {
    std::vector<Instruction> bytecode;
    for (size_t i = 0; i < tokens.size(); ++i) {
        const char* token = tokens[i].c_str();
        if (isEqual(token, "print")) {
            bytecode.push_back({PRINT, 0});
        } else if (isDigit(token[0])) {
            bytecode.push_back({PUSH, toInt(token)});
        } else if (isEqual(token, "+")) {
            bytecode.push_back({ADD, 0});
        } else if (isEqual(token, "-")) {
            bytecode.push_back({SUB, 0});
        }
    }
    return bytecode;
}

// Simple Interpreter (Virtual Machine)
void executeBytecode(const std::vector<Instruction> &bytecode) {
    std::vector<int> stack;
    for (size_t i = 0; i < bytecode.size(); ++i) {
        const Instruction &inst = bytecode[i];
        if (inst.opcode == PUSH) {
            stack.push_back(inst.value);
        } else if (inst.opcode == ADD) {
            if (stack.size() >= 2) {
                int b = stack.back(); stack.pop_back();
                int a = stack.back(); stack.pop_back();
                stack.push_back(a + b);
            }
        } else if (inst.opcode == SUB) {
            if (stack.size() >= 2) {
                int b = stack.back(); stack.pop_back();
                int a = stack.back(); stack.pop_back();
                stack.push_back(a - b);
            }
        } else if (inst.opcode == PRINT) {
            if (!stack.empty()) {
                std::cout << stack.back() << std::endl;
                stack.pop_back();
            }
        }
    }
}

int main() {
    std::string code = "5 3 + print"; // Example input
    auto tokens = tokenize(code);
    auto bytecode = parseAndGenerateBytecode(tokens);
    executeBytecode(bytecode);
    return 0;
}

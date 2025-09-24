#include <iostream>
#include <string>
#include <vector>
#include <string>

std::vector<std::string> split(std::string input) {
    std::vector<std::string> tokens;
    
    for (int i = 0; i < input.length(); i++) {
        std::string token = "";
        for (char ch : input.substr(i)) {
            if (ch == ' ') { break; }
            else {
                token += ch;
                i++;
            }
        }
        tokens.push_back(token);
    }
    return tokens;
}


int main() {
    // Flush after every std::cout / std:cerr
    std::cout << std::unitbuf;
    std::cerr << std::unitbuf;

    while (true) {
        std::cout << "$ ";

        std::string input;
        std::getline(std::cin, input);
        
        std::vector<std::string> inputs = split(input);
        if (inputs[0] == "exit") {
            std::string arg = inputs[1];
            exit(stoi(arg));
        }
        else {
            std::cout << inputs[0] << ": command not found" << std::endl;
        }
    }
}

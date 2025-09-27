#include <iostream>
#include <string>
#include <vector>
#include <string>
#include <functional>
#include <map>
#include <cstdlib>
#include <filesystem>
#include <unistd.h>

using builtin = std::function<void(std::vector<std::string>)>;

std::map<std::string, builtin> builtins;
std::map<std::string, std::string> executables;

std::vector<std::string> split(std::string input, char delimiter) {
    std::vector<std::string> tokens;
    
    for (int i = 0; i < input.length(); i++) {
        std::string token = "";
        for (char ch : input.substr(i)) {
            if (ch == delimiter) { break; }
            else {
                token += ch;
                i++;
            }
        }
        tokens.push_back(token);
    }
    return tokens;
}

void exit_b(std::vector<std::string> args) {
    if (args.size() == 0) {
        exit(0);
    }
    std::string arg = args[0];
    exit(stoi(arg));
}

void echo(std::vector<std::string> args) {
    for (int i = 0; i < args.size(); i++) {
        if (i > 0) std::cout << " ";
            std::cout << args[i];
        }
        std::cout << std::endl;
}

void type(std::vector<std::string> args) {
    if (builtins.contains(args[0])) {
        std::cout << args[0] << " is a shell builtin" << std::endl;
    } else if (executables.contains(args[0])){
        std::cout << args[0] << " is " << executables[args[0]] << std::endl;
    } else {
        std::cout << args[0] << ": not found" << std::endl;
    }
}

int main() {
    // Flush after every std::cout / std:cerr
    std::cout << std::unitbuf;
    std::cerr << std::unitbuf;
    
    builtins["exit"] = exit_b;
    builtins["echo"] = echo;
    builtins["type"] = type;
    builtins["q"] = exit_b;
    
    std::string pathv = std::getenv("PATH");
    std::vector<std::string> paths = split(pathv, ':');
    for (std::string path : paths) {
        if (std::filesystem::exists(std::filesystem::path(path))) {
            for (const std::filesystem::directory_entry& de : std::filesystem::recursive_directory_iterator(path)){
                if (!access(de.path().c_str(), X_OK)) {
                    //std::cout << dir_entry << std::endl;
                    executables.insert({de.path().filename().string(), de.path().string()});
                }
            }
        }
    }

    while (true) {
        std::cout << "$ ";

        std::string input;
        std::getline(std::cin, input);
        
        std::vector<std::string> inputs = split(input, ' ');
        if (inputs.empty()) continue;
        if (builtins[inputs[0]]) {
            std::vector<std::string> args(inputs.begin() + 1, inputs.end());
            builtins[inputs[0]](args);
        } else {
            std::cout << inputs[0] << ": command not found" << std::endl;
        }
    }
}

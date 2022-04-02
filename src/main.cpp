#include <iostream>
#include <string>
#include <fstream>
#include <filesystem>
#include <vector>



void echo(int argc, char *argv[]);
void cat(int argc, char *argv[]);
void ls(int argc, char *argv[]);

int main(int argc, char *argv[]) {
    if (std::string(argv[1]) == "echo") {
        echo(argc, argv);
    } else if (std::string(argv[1]) == "cat") {
        cat(argc, argv);
    } else if (std::string(argv[1]) == "ls") {
        ls(argc, argv);
    } else {
        std::cout << "Available commands: \n" 
                  << "echo <text> \n"
                  << "cat </path/to/file> \n"
                  << "ls </path/to/directory> \n";
    }
    return 0;
}

void echo(int argc, char *argv[]){
    for (int i = 2; i < argc; i++) {
        std::cout << argv[i] << " ";
    }
    std::cout << std::endl;
}

void cat(int argc, char *argv[]) {
    std::ifstream file;
    file.open(argv[2]);

    std::string line;
    if (file.is_open()) {
        while (std::getline(file, line, '\n')) {
            std::cout << line << std::endl;
        }
    }
}

void ls(int argc, char *argv[]) {
    std::string path = argv[2];
    std::vector<std::string> filePaths;
    for (const auto &entry : std::filesystem::directory_iterator(path)) {
        std::string filePath = entry.path().string();
        std::string parsedFileName = filePath.substr(path.length(),filePath.length());
        filePaths.push_back(parsedFileName);
    }

    for (int i = 0; i < filePaths.size(); i++ ) {
        if (filePaths[i].substr(0, 1) != ".") {
            std::cout << filePaths[i];
            if (i != filePaths.size() - 1) {
                 std::cout << "  ";
            }
        }
    }

    std::cout << std::endl;
}
#include <iostream>
#include <string>

void echo(int argc, char *argv[]);

int main(int argc, char *argv[]) {
    if (std::string(argv[1]) == "echo") {
        echo(argc, argv);
    } else {
        std::cout << "Available commands: \n echo <text> \n";
    }
    return 0;
}

void echo(int argc, char *argv[]){
    for (int i = 2; i < argc; i++) {
        std::cout << argv[i] << " ";
    }
    std::cout << std::endl;
}
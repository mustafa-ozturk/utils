#include <iostream>
#include <string>
#include <fstream>
#include <filesystem>
#include <vector>
#include <unistd.h>
#include <limits.h>
#include <sys/utsname.h>

void echo(int argc, char *argv[]);
void cat(int argc, char *argv[]);
void ls(int argc, char *argv[]);
void sysfetch(int argc, char *argv[]);




int main(int argc, char *argv[]) {
    if (argc < 2) {
        std::cout << "Available commands: \n" 
                  << "echo <text> \n"
                  << "cat </path/to/file> \n"
                  << "ls </path/to/directory> \n"
                  << "sysfetch \n";
        return 0;
    }

    if (std::string(argv[1]) == "echo") {
        echo(argc, argv);
    } else if (std::string(argv[1]) == "cat") {
        cat(argc, argv);
    } else if (std::string(argv[1]) == "ls") {
        ls(argc, argv);
    } else if (std::string(argv[1]) == "sysfetch") {
        sysfetch(argc, argv);
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
    // TODO: understand how auto works 
    // TODO: understand how iterator works 
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



void sysfetch(int argc, char *argv[]) {
    // https://man7.org/linux/man-pages/man2/gethostname.2.html
    // https://man7.org/linux/man-pages/man3/getlogin_r.3.html
    char hostname[HOST_NAME_MAX];
    char username[LOGIN_NAME_MAX];
    gethostname(hostname, HOST_NAME_MAX);
    getlogin_r(username, LOGIN_NAME_MAX);
    std::string name = std::string(hostname) + '@' +  std::string(username);

    /*  
        https://man7.org/linux/man-pages/man2/uname.2.html
        uname
        sysname : Linux
        nodename: wooden
        release : 5.16.16-arch1-1
        version : #1 SMP PREEMPT Mon, 21 Mar 2022 22:59:40 +0000
        machine : x86_64
    */

    // /etc/os-release to get distro name

    utsname system;      // declare the variable to hold the result
    uname(&system);      // call the uname() function to fill the struct


    std::string os = std::string(system.sysname) + " " + std::string(system.machine);
    std::string kernel = std::string(system.release);
    // std::cout << system.sysname << std::endl;

    // std::cout << result; // show the result using the helper function

    std::cout << "NAME: " << name << std::endl;   
    // TODO: distro name should be added
    std::cout << "OS: " << os << std::endl;
    std::cout << "KERNEL: " << kernel << std::endl;
}
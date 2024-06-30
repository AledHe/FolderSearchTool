#include <iostream>
#include <string>
#include "tree.h"
#include "matcher.h"

#ifdef _WIN32
#include <windows.h>
#endif

void setUTF8Console() {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
#endif
}

int main(int argc, char** argv) {
    setUTF8Console();

    if (argc < 3) {
        std::cerr << "Usage: " << argv[0] << " <directory_path> <search_pattern>" << std::endl;
        return 1;
    }

    std::string directoryPath = argv[1];
    std::string searchPattern = argv[2];

    std::cout << "Starting the application." << std::endl;
    std::cout << "Directory path: " << directoryPath << std::endl;
    std::cout << "Search pattern: " << searchPattern << std::endl;

    try {
        FileTree tree;
        tree.addNode(directoryPath);

        std::cout << "Searching for pattern..." << std::endl;
        std::vector<std::string> results = tree.search(searchPattern);
        std::cout << "Search completed. " << results.size() << " matches found." << std::endl;

        for (const auto& file : results) {
            std::cout << "Match found: " << file << std::endl;
        }
    } catch (const std::exception& e) {
        std::cerr << "An error occurred: " << e.what() << std::endl;
        return 1;
    }

    std::cout << "Exited." << std::endl;
    return 0;
}
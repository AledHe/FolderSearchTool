#include <iostream>
#include "tree.h"
#include "matcher.h"

int main(int argc, char** argv) {

    system("chcp 65001"); // set console code page to UTF-8

    if (argc < 3) {
        std::cerr << "Usage: " << argv[0] << " <directory_path> <search_pattern>" << std::endl;
        return 1;
    }

    std::string directoryPath = argv[1];
    std::string searchPattern = argv[2];

    std::cout << "Starting the application." << std::endl;
    std::cout << "Directory path: " << directoryPath << std::endl;
    std::cout << "Search pattern: " << searchPattern << std::endl;

    FileTree tree;
    tree.addNode(directoryPath);

    std::cout << "Searching for pattern..." << std::endl;
    std::vector<std::string> results = tree.search(searchPattern);
    std::cout << "Search completed. " << results.size() << " matches found." << std::endl;

    for (const auto& file : results) {
        if (Matcher::match(file, searchPattern)) {
            std::cout << "Match found: " << file << std::endl;
        } else {
            std::cout << "False positive match: " << file << std::endl;
        }
    }

    std::cout << "Exited." << std::endl;
    return 0;
}
#include "tree.h"
#include <sstream>
#include <algorithm>
#include <filesystem>
#include <iostream>
#include <matcher.h>

namespace fs = std::filesystem;

FileTree::FileTree() {
    root = std::make_shared<TreeNode>("root", "root");
}

void FileTree::addNode(const std::string& path) {
    if (!std::filesystem::exists(path) || !std::filesystem::is_directory(path)) {
        std::cerr << "Error: Invalid directory path: " << path << std::endl;
        return;
    } // error search root.

    // call addNodeHelper directly for each entry without checking if it's a directory
    for (const auto& entry : fs::recursive_directory_iterator(path)) {
        addNodeHelper(entry.path().string(), root);
    }
}

void FileTree::addNodeHelper(const std::string& path, std::shared_ptr<TreeNode> node) {
    std::filesystem::path fsPath = path;
    // Keep track of the current path as we traverse the tree nodes
    std::string currentPath = node->fullPath;

    for (const auto& part : fsPath) {
        // Append the next part of the path
        currentPath = (currentPath / part).string();

        auto it = std::find_if(node->children.begin(), node->children.end(),
                               [&part](const std::shared_ptr<TreeNode>& child) { return child->name == part.filename().string(); });

        if (it == node->children.end()) {
            // Create a new node with the updated currentPath
            std::shared_ptr<TreeNode> newNode = std::make_shared<TreeNode>(part.filename().string(), currentPath);
            node->children.push_back(newNode);
            node = newNode; // Continue from the new node
        } else {
            node = *it; // Move to the existing child node
        }

        // Update currentPath for the next iteration
        currentPath = node->fullPath;
    }
}

std::vector<std::string> FileTree::search(const std::string& pattern) const {
    std::vector<std::string> results;
    searchHelper(pattern, root, results);
    return results;
}

void FileTree::searchHelper(const std::string& pattern, std::shared_ptr<TreeNode> node, std::vector<std::string>& results) const {
    if (Matcher::match(node->name, pattern)) {
        results.push_back(node->fullPath);
    }
    for (auto& child : node->children) {
        searchHelper(pattern, child, results);
    }
}
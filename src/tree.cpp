#include "tree.h"
#include "matcher.h"
#include <filesystem>
#include <iostream>
#include <algorithm>

namespace fs = std::filesystem;

FileTree::FileTree() : root(std::make_shared<TreeNode>("root", "root")) {}

void FileTree::addNode(const std::string& path) {
    if (!fs::exists(path) || !fs::is_directory(path)) {
        std::cerr << "Error: Invalid directory path: " << path << std::endl;
        return;
    }

    for (const auto& entry : fs::recursive_directory_iterator(path)) {
        addNodeHelper(entry.path().string(), root);
    }
}

void FileTree::addNodeHelper(const std::string& path, std::shared_ptr<TreeNode> node) {
    std::cout << "Adding node: " << path << std::endl;

    fs::path fsPath = path;
    std::string currentPath = node->fullPath;

    for (const auto& part : fsPath) {
        currentPath = (fs::path(currentPath) / part).string();
        std::cout << "Current path: " << currentPath << std::endl;

        auto it = std::find_if(node->children.begin(), node->children.end(),
                               [&part](const auto& child) { return child->name == part.filename().string(); });

        if (it == node->children.end()) {
            std::cout << "Node not found, creating new node" << std::endl;
            auto newNode = std::make_shared<TreeNode>(part.filename().string(), currentPath);
            node->children.push_back(newNode);
            node = newNode;
        } else {
            std::cout << "Node found, moving to next child" << std::endl;
            node = *it;
        }
    }
}

std::vector<std::string> FileTree::search(const std::string& pattern) const {
    std::vector<std::string> results;
    searchHelper(pattern, root, results);
    return results;
}

void FileTree::searchHelper(const std::string& pattern, const std::shared_ptr<TreeNode>& node, std::vector<std::string>& results) const {
    if (Matcher::match(node->name, pattern)) {
        results.push_back(node->fullPath);
    }
    for (const auto& child : node->children) {
        searchHelper(pattern, child, results);
    }
}

void FileTree::traverseTree(const std::function<void(const TreeNode&)>& callback) const {
    traverseTreeHelper(root, callback);
}

void FileTree::traverseTreeHelper(const std::shared_ptr<TreeNode>& node, const std::function<void(const TreeNode&)>& callback) const {
    callback(*node);
    for (const auto& child : node->children) {
        traverseTreeHelper(child, callback);
    }
}
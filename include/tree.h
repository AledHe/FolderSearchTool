#ifndef FILE_TREE_H
#define FILE_TREE_H

#include <string>
#include <vector>
#include <memory>
#include <queue>

class TreeNode {
public:
    std::string name;
    std::string fullPath;
    std::vector<std::shared_ptr<TreeNode>> children;

    TreeNode(const std::string& name, const std::string& fullPath) : name(name), fullPath(fullPath) {}
};

class FileTree {
private:
    std::shared_ptr<TreeNode> root;
    void addNodeHelper(const std::string& path, std::shared_ptr<TreeNode> node);
    void searchHelper(const std::string& pattern, std::shared_ptr<TreeNode> node, std::vector<std::string>& results) const;

public:
    FileTree();
    void addNode(const std::string& path);
    std::vector<std::string> search(const std::string& pattern) const;
};

#endif // FILE_TREE_H

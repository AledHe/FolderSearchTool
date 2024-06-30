#ifndef FILE_TREE_H
#define FILE_TREE_H

#include <string>
#include <vector>
#include <memory>
#include <functional>

class TreeNode {
public:
    std::string name;
    std::string fullPath;
    std::vector<std::shared_ptr<TreeNode>> children;

    TreeNode(std::string name, std::string fullPath) : name(std::move(name)), fullPath(std::move(fullPath)) {}
};

class FileTree {
private:
    std::shared_ptr<TreeNode> root;
    void addNodeHelper(const std::string& path, std::shared_ptr<TreeNode> node);
    void searchHelper(const std::string& pattern, const std::shared_ptr<TreeNode>& node, std::vector<std::string>& results) const;

public:
    FileTree();
    void addNode(const std::string& path);
    std::vector<std::string> search(const std::string& pattern) const;
    void traverseTree(const std::function<void(const TreeNode&)>& callback) const;

private:
    void traverseTreeHelper(const std::shared_ptr<TreeNode>& node, const std::function<void(const TreeNode&)>& callback) const;
};

#endif // FILE_TREE_H
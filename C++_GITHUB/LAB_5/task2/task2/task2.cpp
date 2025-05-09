#include <iostream>
#include <queue>

class TreeNode {
public:
    int data;
    TreeNode* left = nullptr;
    TreeNode* right = nullptr;

    TreeNode(int val) : data(val) {}
};

class Tree {
protected:
    TreeNode* root = nullptr;

public:
    virtual ~Tree() {
        destroy(root);
    }

    virtual void insert(int data) = 0;

    void destroy(TreeNode* node) {
        if (node) {
            destroy(node->left);
            destroy(node->right);
            delete node;
        }
    }

    void inOrder(TreeNode* node) const {
        if (node) {
            inOrder(node->left);
            std::cout << node->data << " ";
            inOrder(node->right);
        }
    }

    void inOrderTraversal() const {
        std::cout << "In-Order Traversal: ";
        inOrder(root);
        std::cout << "\n";
    }

    void breadthFirstTraversal() const {
        if (!root) {
            std::cout << "Tree is empty.\n";
            return;
        }

        std::queue<TreeNode*> q;
        q.push(root);

        std::cout << "Breadth-First Traversal: ";
        while (!q.empty()) {
            TreeNode* curr = q.front(); q.pop();
            std::cout << curr->data << " ";
            if (curr->left) q.push(curr->left);
            if (curr->right) q.push(curr->right);
        }
        std::cout << "\n";
    }
};

class BinarySearchTree : public Tree {
private:
    TreeNode* insertNode(TreeNode* node, int data) {
        if (!node) return new TreeNode(data);
        if (data < node->data) node->left = insertNode(node->left, data);
        else if (data > node->data) node->right = insertNode(node->right, data);
        return node;
    }

public:
    void insert(int data) override {
        root = insertNode(root, data);
    }
};

int main() {
    Tree* tree = new BinarySearchTree();

    int value;
    std::cout << "Enter integers to insert into tree (non-number to stop): ";
    while (std::cin >> value) {
        tree->insert(value);
    }

    std::cin.clear();
    std::cin.ignore();

    std::cout << "\n--- Traversals ---\n";
    tree->breadthFirstTraversal();
    tree->inOrderTraversal();

    delete tree;

    std::cout << "--- Program End ---\n";
    return 0;
}

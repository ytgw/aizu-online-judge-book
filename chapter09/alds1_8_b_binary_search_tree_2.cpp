#include<iostream>
#include<cmath>


class Node {
public:
    int key;
    Node *parent, *left, *right;

    Node() : key(0), parent(nullptr), left(nullptr), right(nullptr) {}
    Node(int key) : key(key), parent(nullptr), left(nullptr), right(nullptr) {}
};


class BinarySearchTree {
public:
    BinarySearchTree(const int maxNodeNum) : root(nullptr), nodeNum(0) {
        nodes = new Node[maxNodeNum];
    }
    ~BinarySearchTree() {
        delete[] nodes;
    }

    void insert(const int key) {
        Node *z = &nodes[nodeNum];
        z->key = key;
        z->parent = nullptr;
        z->left = nullptr;
        z->right = nullptr;
        nodeNum++;

        Node *y = nullptr;
        Node *x = root;

        while (x != nullptr) {
            y = x;
            if (z->key < x->key) {
                x = x->left;
            } else {
                x = x->right;
            }
        }
        z->parent = y;

        if (y == nullptr) {
            root = z;
        } else if (z->key < y->key) {
            y->left = z;
        } else {
            y->right = z;
        }
    }

    bool find(const int key) const {
        Node* node = root;
        bool isContain = false;
        while (node != nullptr) {
            if (node->key == key) {
                isContain = true;
                break;
            } else if (node->key < key) {
                node = node->right;
            } else {
                node = node->left;
            }
        }
        return isContain;
    }

    void printPreOrder() const {
        printPreOrder(root);
        std::cout << std::endl;
    }

    void printInOrder() const {
        printInOrder(root);
        std::cout << std::endl;
    }

private:
    Node *root, *nodes;
    int nodeNum;

    void printPreOrder(const Node* root) const {
        if (root == nullptr) return;

        std::cout << " " << root->key;
        printPreOrder(root->left);
        printPreOrder(root->right);
    }

    void printInOrder(const Node* root) const {
        if (root == nullptr) return;

        printInOrder(root->left);
        std::cout << " " << root->key;
        printInOrder(root->right);
    }
};


int main() {
    int commandNum;
    std::cin >> commandNum;
    if (!(commandNum <= 5 * std::pow(10, 5))) {
        std::cerr << "commandNum is invalid." << std::endl;
        exit(EXIT_FAILURE);
    }

    BinarySearchTree tree(commandNum);
    for (int i=0; i<commandNum; i++) {
        std::string command;
        int key;
        std::cin >> command;
        if (command == "print") {
            tree.printInOrder();
            tree.printPreOrder();
        } else if (command == "insert") {
            std::cin >> key;
            if (!(-2 * std::pow(10,9) <= key <= 2 * std::pow(10,9))) {
                std::cerr << "key is invalid." << std::endl;
                exit(EXIT_FAILURE);
            }
            tree.insert(key);
        } else if (command == "find") {
            std::cin >> key;
            if (!(-2 * std::pow(10,9) <= key <= 2 * std::pow(10,9))) {
                std::cerr << "key is invalid." << std::endl;
                exit(EXIT_FAILURE);
            }
            if (tree.find(key)) {
                std::cout << "yes" << std::endl;
            } else {
                std::cout << "no" << std::endl;
            }
        } else {
            std::cerr << "command is invalid." << std::endl;
            exit(EXIT_FAILURE);
        }
    }

    return 0;
}

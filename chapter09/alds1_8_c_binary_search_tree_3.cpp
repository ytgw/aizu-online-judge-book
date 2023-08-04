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
        if (findNode(key) == nullptr) {
            return false;
        } else {
            return true;
        }
    }

    bool deleteNode(const int key) {
        Node* node = findNode(key);
        if (node == nullptr) {
            return false;
        } else {
            deleteNode(node);
            return true;
        }
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

    Node* findNode(const int key) const {
        Node* node = root;
        while (node != nullptr) {
            if (node->key == key) {
                break;
            } else if (node->key < key) {
                node = node->right;
            } else {
                node = node->left;
            }
        }
        return node;
    }

    int getChildNum(const Node* node) const {
        int childNum = 0;
        if (node->left != nullptr) childNum++;
        if (node->right != nullptr) childNum++;
        return childNum;
    }

    Node* getChild(const Node* node) const {
        if (node->left != nullptr) {
            return node->left;
        } else if (node->right != nullptr) {
            return node->right;
        }
        return nullptr;
    }

    Node* getSuccessor(Node* node) const {
        Node* successor = node;
        while (successor->left != nullptr) {
            successor = successor->left;
        }
        return successor;
    }

    void deleteNode(Node* node) {
        Node* parent = node->parent;

        // 子の数で場合分けする
        const int childNum = getChildNum(node);

        if (childNum == 0) {
            // 子を持たない場合
            // 親の更新
            if (parent != nullptr) {
                if (parent->left == node) {
                    parent->left = nullptr;
                } else {
                    parent->right = nullptr;
                }
            }

            return;
        } else if (childNum == 1) {
            // 子を1つ持つ場合
            // 子の更新
            Node* child = getChild(node);
            child->parent = parent;

            // 親の更新
            if (parent != nullptr) {
                if (parent->left == node) {
                    parent->left = child;
                } else {
                    parent->right = child;
                }
            } else {
                root = child;
            }

            return;
        } else {
            // 子を2つ持つ場合
            Node* successor = getSuccessor(node);
            const int successorChildNum = getChildNum(successor);

            if (successorChildNum == 0) {
                node->key = successor->key;
                if (successor->parent->left == successor) {
                    successor->parent->left = nullptr;
                } else {
                    successor->parent->right = nullptr;
                }
            } else {
                node->key = successor->key;
                if (successor->parent->left == successor) {
                    successor->parent->left = nullptr;
                } else {
                    successor->parent->right = nullptr;
                }
            }
        }
    }

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
        } else if (command == "delete") {
            std::cin >> key;
            if (!(-2 * std::pow(10,9) <= key <= 2 * std::pow(10,9))) {
                std::cerr << "key is invalid." << std::endl;
                exit(EXIT_FAILURE);
            }
            tree.deleteNode(key);
        } else {
            std::cerr << "command is invalid." << std::endl;
            exit(EXIT_FAILURE);
        }
    }

    return 0;
}

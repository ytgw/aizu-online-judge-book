#include<iostream>
#include<cmath>

const int NILL_ID = -1;


class Node {
public:
    Node() : parentID(NILL_ID), leftID(NILL_ID), rightID(NILL_ID) {}
    void setParent(const int parentID) {
        this->parentID = parentID;
    }
    int getParent() {
        return parentID;
    }
    void setChildren(const int leftID, const int rightID) {
        this->leftID = leftID;
        this->rightID = rightID;
    }
    int getLeft() const {
        return leftID;
    }
    int getRight() const {
        return rightID;
    }
    int getDegree() const {
        int degree = 0;
        if (leftID != NILL_ID) degree++;
        if (rightID != NILL_ID) degree++;
        return degree;
    }
    std::string getType() const {
        if (parentID == NILL_ID) {
            return "root";
        } else if (leftID == NILL_ID && rightID == NILL_ID) {
            return "leaf";
        } else {
            return "internal node";
        }
    }
private:
    int parentID, leftID, rightID;
};


class BinaryTree {
public:
    BinaryTree(const int nodeNum) : nodeNum(nodeNum) {
        nodes = new Node[nodeNum];
    }
    ~BinaryTree() {
        delete[] nodes;
    }
    void setNode(const int nodeID, const int leftID, const int rightID) {
        nodes[nodeID].setChildren(leftID, rightID);
        if (leftID != NILL_ID) nodes[leftID].setParent(nodeID);
        if (rightID != NILL_ID) nodes[rightID].setParent(nodeID);
    }
    int getRoot() const {
        int nodeID = 0;
        while (nodes[nodeID].getParent() != NILL_ID) {
            nodeID = nodes[nodeID].getParent();
        }
        return nodeID;
    }
    void printPreorder(const int nodeID) const {
        if (nodeID == NILL_ID) return;

        std::cout << " " << nodeID;
        printPreorder(nodes[nodeID].getLeft());
        printPreorder(nodes[nodeID].getRight());
    }
    void printInorder(const int nodeID) const {
        if (nodeID == NILL_ID) return;

        printInorder(nodes[nodeID].getLeft());
        std::cout << " " << nodeID;
        printInorder(nodes[nodeID].getRight());
    }
    void printPostorder(const int nodeID) const {
        if (nodeID == NILL_ID) return;

        printPostorder(nodes[nodeID].getLeft());
        printPostorder(nodes[nodeID].getRight());
        std::cout << " " << nodeID;
    }
private:
    Node* nodes;
    const int nodeNum;
};


int main() {
    // 標準入力からのデータ取得
    int nodeNum;
    std::cin >> nodeNum;
    if (!(1 <= nodeNum <= 25)) {
        std::cerr << "nodeNum is invalid.";
        exit(EXIT_FAILURE);
    }

    BinaryTree tree = BinaryTree(nodeNum);
    for (int i=0; i<nodeNum; i++) {
        int nodeID, leftID, rightID;
        std::cin >> nodeID >> leftID >> rightID;

        tree.setNode(nodeID, leftID, rightID);
    }

    // 結果表示
    std::cout << "Preorder" << std::endl;
    tree.printPreorder(tree.getRoot());
    std::cout << std::endl;

    std::cout << "Inorder" << std::endl;
    tree.printInorder(tree.getRoot());
    std::cout << std::endl;

    std::cout << "Postorder" << std::endl;
    tree.printPostorder(tree.getRoot());
    std::cout << std::endl;

    return 0;
}

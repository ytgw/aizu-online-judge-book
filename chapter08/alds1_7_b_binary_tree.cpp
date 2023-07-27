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
    int getDepth(const int nodeID) const {
        int depth = 0, checkID = nodeID;
        while (nodes[checkID].getType() != "root") {
            checkID = nodes[checkID].getParent();
            depth++;
        }
        return depth;
    }
    int getSibling(const int nodeID) const {
        const int parentID = nodes[nodeID].getParent();
        if (parentID == NILL_ID) {
            return NILL_ID;
        }

        int leftSiblingID = nodes[parentID].getLeft();
        if (leftSiblingID != NILL_ID && leftSiblingID != nodeID) {
            return leftSiblingID;
        }

        int rightSiblingID = nodes[parentID].getRight();
        if (rightSiblingID != NILL_ID && rightSiblingID != nodeID) {
            return rightSiblingID;
        }

        return NILL_ID;
    }
    int getHeight(const int nodeID) const {
        const int leftID = nodes[nodeID].getLeft();
        const int rightID = nodes[nodeID].getRight();

        int leftHeight = 0, rightHeight = 0;
        if (leftID != NILL_ID) leftHeight = getHeight(leftID) + 1;
        if (rightID != NILL_ID) rightHeight = getHeight(rightID) + 1;
        return std::max(leftHeight, rightHeight);
    }
    void print() const {
        for (int nodeID=0; nodeID<nodeNum; nodeID++) {
            std::cout << "node " << nodeID << ": ";
            std::cout << "parent = " << nodes[nodeID].getParent();
            std::cout << ", sibling = " << getSibling(nodeID);
            std::cout << ", degree = " << nodes[nodeID].getDegree();
            std::cout << ", depth = " << getDepth(nodeID);
            std::cout << ", height = " << getHeight(nodeID);
            std::cout << ", " << nodes[nodeID].getType();
            std::cout << std::endl;
        }
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

    tree.print();

    return 0;
}

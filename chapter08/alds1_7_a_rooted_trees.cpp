#include<iostream>
#include<cmath>


class Node {
public:
    Node() : parentID(nillID), childrenNum(0) {
        this->childrenIDs = new int[childrenNum];
    }
    ~Node() {
        delete[] childrenIDs;
    }
    void setParent(const int parentID) {
        this->parentID = parentID;
    }
    int getParent() {
        return parentID;
    }
    void setChildren(const int childrenIDs[], const int childrenNum) {
        this->childrenNum = childrenNum;
        this->childrenIDs = new int[childrenNum];
        for (int i=0; i<childrenNum; i++) {
            this->childrenIDs[i] = childrenIDs[i];
        }
    }
    std::string getType() const {
        if (parentID == nillID) {
            return "root";
        } else if (childrenNum == 0) {
            return "leaf";
        } else {
            return "internal node";
        }
    }
    std::string getChildrenString() const {
        std::string children = "[";
        for (int i=0; i<childrenNum; i++) {
            children += std::to_string(childrenIDs[i]);
            if (i != childrenNum - 1) {
                children += ", ";
            }
        }
        children += "]";
        return children;
    }
private:
    int parentID, childrenNum;
    int* childrenIDs;
    const static int nillID = -1;
};


class Tree {
public:
    Tree(const int nodeNum) : nodeNum(nodeNum) {
        nodes = new Node[nodeNum];
    }
    ~Tree() {
        delete[] nodes;
    }
    void setNode(const int nodeID, const int childrenIDs[], const int childrenNum) {
        nodes[nodeID].setChildren(childrenIDs, childrenNum);
        for (int i=0; i<childrenNum; i++) nodes[childrenIDs[i]].setParent(nodeID);
    }
    int getDepth(const int nodeID) const {
        int depth = 0, checkID = nodeID;
        while (nodes[checkID].getType() != "root") {
            checkID = nodes[checkID].getParent();
            depth++;
        }
        return depth;
    }
    void print() const {
        for (int nodeID=0; nodeID<nodeNum; nodeID++) {
            std::cout << "node " << nodeID << ": ";
            std::cout << "parent = " << nodes[nodeID].getParent();
            std::cout << ", depth = " << getDepth(nodeID);
            std::cout << ", " << nodes[nodeID].getType();
            std::cout << ", " << nodes[nodeID].getChildrenString();
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
    if (!(1 <= nodeNum <= std::pow(10,5))) {
        std::cerr << "nodeNum is invalid.";
        exit(EXIT_FAILURE);
    }

    Tree tree = Tree(nodeNum);
    for (int i=0; i<nodeNum; i++) {
        int nodeID, childrenNum;
        std::cin >> nodeID >> childrenNum;
        if (!(0 <= nodeID <= nodeNum)) {
            std::cerr << "nodeID is invalid.";
            exit(EXIT_FAILURE);
        }

        int childrenIDs[childrenNum];
        for (int i=0; i<childrenNum; i++) {
            std::cin >> childrenIDs[i];
        }

        tree.setNode(nodeID, childrenIDs, childrenNum);
    }

    tree.print();

    return 0;
}

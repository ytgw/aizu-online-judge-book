#include<cassert>
#include<cmath>
#include<iostream>
#include<vector>


class DisjointSet {
public:
    DisjointSet(const int elementNum) : elementNum(elementNum) {
        parents = std::vector<int>(elementNum);

        for (int i = 0; i < elementNum; i++) {
            makeSet(i);
        }
    }

    void unite(const int x, const int y) {
        const int root = findRoot(x);
        updateParents(x, root);
        updateParents(y, root);
        // print();
    }

    bool same(const int x, const int y) const {
        if (findRoot(x) == findRoot(y)) {
            return true;
        } else {
            return false;
        }
    }

private:
    const int elementNum;
    std::vector<int> parents;

    void makeSet(const int x) {
        parents[x] = x;
    }

    void updateParents(int x, const int root) {
        while (x != parents[x]) {
            int parent = parents[x];
            parents[x] = root;
            x = parent;
        }
        parents[x] = root;
    }

    int findRoot(int x) const {
        while (x != parents[x]) {
            x = parents[x];
        }
        return x;
    }

    void print() const {
        std::cout << "(x, set(x)): ";
        for (int i = 0; i < elementNum; i++) {
            printf("(id=%d, parent=%d, root=%d), ", i, parents[i], findRoot(i));
        }
        std::cout << std::endl;
    }
};



int main() {
    int elementNum, queryNum;
    std::cin >> elementNum >> queryNum;
    assert(1 <= elementNum && elementNum <= std::pow(10,4));
    assert(1 <= queryNum && queryNum <= std::pow(10,5));

    DisjointSet disjointSet = DisjointSet(elementNum);
    for (int _ = 0; _ < queryNum; _++) {
        int command, x, y;
        std::cin >> command >> x >> y;
        assert(command == 0 || command == 1);
        assert(0 <= x && x <= elementNum - 1);
        assert(0 <= y && y <= elementNum - 1);

        if (command == 0) {
            disjointSet.unite(x, y);
        } else if (command == 1) {
            std::cout << (int)disjointSet.same(x, y) << std::endl;
        }
    }

    return 0;
}

#include<algorithm>
#include<cassert>
#include<cmath>
#include<iostream>
#include<vector>


class Point {
public:
    int id, x, y;
    Point() {}
    Point(const int id, const int x, const int y) : id(id), x(x), y(y) {}
    std::string toString() const {
        std::string str = "{id: " + std::to_string(id);
        str += ", x: " + std::to_string(x);
        str += ", y: " + std::to_string(y) + "}";
        return str;
    }
    void print() const {
        printf("%d\n", id);
    }
};


class Node {
public:
    Point *point;
    Node *left, *right;
    Node() : point(nullptr), left(nullptr), right(nullptr) {}
    bool hasLeft() const {
        return left != nullptr;
    }
    bool hasRight() const {
        return right != nullptr;
    }
    std::string toString() const {
        std::string pointStr, leftStr, rightStr;

        pointStr = point->toString();
        if (hasLeft()) {
            leftStr = left->point->toString();
        } else {
            leftStr = "nullptr";
        }
        if (hasRight()) {
            rightStr = right->point->toString();
        } else {
            rightStr = "nullptr";
        }

        std::string str = "{point: " + pointStr + ", left: " + leftStr + ", right: " + rightStr + "}";
        return str;
    }
};


class TwoDimensionTree {
public:
    TwoDimensionTree(const int pointNum) : pointNum(pointNum), nodeIdx(0) {
        points = std::vector<Point>(pointNum);
        nodes = std::vector<Node>(pointNum);
    }

    void setPoint(const int id, const int x, const int y) {
        points[id].id = id;
        points[id].x = x;
        points[id].y = y;
    }

    Node* makeTree(const int left, const int right, const int depth) {
        if (!(left < right)) return nullptr;

        const int updateIdx = nodeIdx;
        nodeIdx++;
        const int mid = sortAndGetMid(left, right, depth);

        nodes[updateIdx].point = &points[mid];
        nodes[updateIdx].left = makeTree(left, mid, depth + 1);
        nodes[updateIdx].right = makeTree(mid + 1, right, depth + 1);

        return &nodes[updateIdx];
    }

    void printNodes() const {
        for (int i = 0; i < pointNum; i++) {
            std::cout << nodes[i].toString() << std::endl;
        }
    }

    void printFoundNodes(const int minX, const int maxX, const int minY, const int maxY) const {
        std::vector<int> foundIds;
        findPoints(&nodes[0], 0, minX, maxX, minY, maxY, foundIds);

        std::sort(foundIds.begin(), foundIds.end());
        for (int i = 0; i < foundIds.size(); i++) {
            std::cout << foundIds[i] << std::endl;
        }
        std::cout << std::endl;
    }

private:
    const int pointNum;
    std::vector<Point> points;
    std::vector<Node> nodes;
    int nodeIdx;

    bool shouldSortByX(const int depth) const {
        return depth % 2 == 0;
    }

    int sortAndGetMid(const int left, const int right, const int depth) {
        auto lessX = [](const Point p1, const Point p2) {return p1.x < p2.x;};
        auto lessY = [](const Point p1, const Point p2) {return p1.y < p2.y;};

        if (shouldSortByX(depth)) {
            std::sort(points.begin() + left, points.begin() + right, lessX);
        } else {
            std::sort(points.begin() + left, points.begin() + right, lessY);
        }

        return (left + right) / 2;
    }

    void findPoints(
        const Node *root,
        const int depth,
        const int minX,
        const int maxX,
        const int minY,
        const int maxY,
        std::vector<int>& foundIds
    ) const {
        // pointのidをfoundIdsに入れる。

        Point point = *root->point;
        int x = point.x;
        int y = point.y;

        if (minX <= x && x <= maxX && minY <= y && y <= maxY) {
            foundIds.push_back(point.id);
        }

        if (shouldSortByX(depth)) {
            if (root->hasLeft() && minX <= x) {
                findPoints(root->left, depth + 1, minX, maxX, minY, maxY, foundIds);
            }
            if (root->hasRight() && x <= maxX) {
                findPoints(root->right, depth + 1, minX, maxX, minY, maxY, foundIds);
            }
        } else {
            if (root->hasLeft() && minY <= y) {
                findPoints(root->left, depth + 1, minX, maxX, minY, maxY, foundIds);
            }
            if (root->hasRight() && y <= maxY) {
                findPoints(root->right, depth + 1, minX, maxX, minY, maxY, foundIds);
            }
        }
    }
};


void debug() {
    const int pointNum = 4;
    TwoDimensionTree tree = TwoDimensionTree(pointNum);

    const int x[pointNum] = {1,2,3,4};
    const int y[pointNum] = {11,12,13,10};

    for (int i = 0; i < pointNum; i++) {
        tree.setPoint(i, x[i], y[i]);
    }

    tree.makeTree(0, pointNum, 0);
    tree.printNodes();
    tree.printFoundNodes(2, 3, 10, 13);
}


int main() {
    int pointNum;
    std::cin >> pointNum;
    assert(0 <= pointNum && pointNum <= 5 * std::pow(10,5));

    TwoDimensionTree tree = TwoDimensionTree(pointNum);

    int x[pointNum], y[pointNum];
    for (int i = 0; i < pointNum; i++) {
        int x, y;
        scanf("%d", &x);
        scanf("%d", &y);
        tree.setPoint(i, x, y);
    }

    // 木の構築
    tree.makeTree(0, pointNum, 0);

    int queryNum;
    std::cin >> queryNum;
    assert(0 <= queryNum && queryNum <= 2 * std::pow(10,4));

    for (int _ = 0; _ < queryNum; _++) {
        int minX, maxX, minY, maxY;
        scanf("%d", &minX);
        scanf("%d", &maxX);
        scanf("%d", &minY);
        scanf("%d", &maxY);
        // std::cin >> minX >> maxX >> minY >> maxY;

        tree.printFoundNodes(minX, maxX, minY, maxY);
    }

    return 0;
}

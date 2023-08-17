#include<algorithm>
#include<cassert>
#include<cmath>
#include<iostream>
#include<vector>


struct Point {
    int x, y;

    int calcDotProduct(const Point p) const {
        return x * p.x + y * p.y;
    }

    int calcCrossProductSize(const Point p) const{
        return std::abs(x * p.y - y * p.x);
    }
};


typedef Point Vector;


class Line {
public:
    Line(const Point p1, const Point p2) : p1(p1), p2(p2) {}

    Vector getVector() const {
        Vector p;
        p.x = p2.x - p1.x;
        p.y = p2.y - p1.y;
        return p;
    }

    bool isSizeZero() const {
        bool result = (p1.x == p2.x) && (p1.y == p2.y);
        return result;
    }

private:
    const Point p1, p2;
};



void printRelation(const Line line1, const Line line2) {
    const int parallel = 2, orthogonal = 1, other = 0;

    const Vector v1 = line1.getVector();
    const Vector v2 = line2.getVector();

    const int dotProduct = v1.calcDotProduct(v2);
    const int crossProductSize = v1.calcCrossProductSize(v2);

    int relation;
    if (line1.isSizeZero() || line2.isSizeZero()) {
        relation = other;
    } else if (crossProductSize == 0) {
        // 並行の判定
        relation = parallel;
    } else if (dotProduct == 0) {
        // 直行の判定
        relation = orthogonal;
    } else {
        relation = other;
    }

    std::cout << relation << std::endl;
}


int main() {
    int queryNum;
    std::cin >> queryNum;
    assert(1 <= queryNum && queryNum <= std::pow(10,3));

    for (int _ = 0; _ < queryNum; _++) {
        Point p0, p1, p2, p3;
        std::cin >> p0.x >> p0.y;
        std::cin >> p1.x >> p1.y;
        std::cin >> p2.x >> p2.y;
        std::cin >> p3.x >> p3.y;

        const auto line1 = Line(p0, p1);
        const auto line2 = Line(p2, p3);
        printRelation(line1, line2);
    }

    return 0;
}

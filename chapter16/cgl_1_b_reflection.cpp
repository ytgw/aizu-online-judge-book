#include<algorithm>
#include<cassert>
#include<cmath>
#include<iostream>
#include<vector>


const double EPS = 1e-10;


class Point {
public:
    double x, y;

    Point(const double x, const double y) : x(x), y(y) {}
    Point operator + (const Point p) const {return Point(x + p.x, y + p.y);}
    Point operator - (const Point p) const {return Point(x - p.x, y - p.y);}
    Point operator * (const double a) const {return Point(a*x, a*y);}
    Point operator / (const double a) const {return Point(x/a, y/a);}
    bool operator == (const Point p) const {
        return std::abs(x - p.x) < EPS && std::abs(y - p.y) < EPS;
    }

    double norm() const {return x*x + y*y;}
    double abs() const {return std::sqrt(norm());}
};


typedef Point Vector;


double calcDotProduct(const Vector v1, const Vector v2) {
    return v1.x * v2.x + v1.y * v2.y;
}


class Line {
public:
    Line(const Point p1, const Point p2) : p1(p1), p2(p2) {}

    Point calcProjectionPoint(const Point p) const {
        Vector base = p2 - p1;
        Vector hypo = p - p1;

        // 射影点からp1までの距離
        const double distance = calcDotProduct(hypo, base) / base.abs();

        return p1 + base * distance / base.abs();
    }

    Point calcReflectionPoint(const Point p) const {
        const Point projectionPoint = calcProjectionPoint(p);

        return p + (projectionPoint - p) * 2;
    }

private:
    const Point p1, p2;
};


int main() {
    double x1, y1, x2, y2;
    std::cin >> x1 >> y1 >> x2 >> y2;
    const auto line = Line(Point(x1, y1), Point(x2, y2));

    int queryNum;
    std::cin >> queryNum;
    assert(1 <= queryNum && queryNum <= std::pow(10,3));

    for (int _ = 0; _ < queryNum; _++) {
        double x, y;
        std::cin >> x >> y;

        const Point reflectedPoint = line.calcReflectionPoint(Point(x, y));
        printf("%.10f %.10f\n", reflectedPoint.x, reflectedPoint.y);
    }

    return 0;
}

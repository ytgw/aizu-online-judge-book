#include<algorithm>
#include<cassert>
#include<cmath>
#include<iostream>
#include<vector>


const double EPS = 1e-10;


enum class SegmentPointRelation {
    COUNTER_CLOCKWISE,
    CLOCKWISE,
    ONLINE_BACK,
    ONLINE_FRONT,
    ON_SEGMENT,
};


class Point {
public:
    const double x, y;

    Point(const double x, const double y) : x(x), y(y) {}
    Point operator + (const Point p) const {return Point(x + p.x, y + p.y);}
    Point operator - (const Point p) const {return Point(x - p.x, y - p.y);}
    Point operator * (const double a) const {return Point(a*x, a*y);}
    Point operator / (const double a) const {return Point(x/a, y/a);}
    bool operator == (const Point p) const {
        return std::abs(x - p.x) < EPS && std::abs(y - p.y) < EPS;
    }

    double norm() const {
        const double squaredNorm = x*x + y*y;
        return std::sqrt(squaredNorm);
    }
};


typedef Point Vector;


double calcDistance(const Point p1, const Point p2) {
    return (p2 - p1).norm();
}


double calcDotProduct(const Vector v1, const Vector v2) {
    return v1.x * v2.x + v1.y * v2.y;
}


double calcCrossProduct(const Vector v1, const Vector v2) {
    return v1.x * v2.y - v1.y * v2.x;
}


class Line {
public:
    const Point p1, p2;

    Line(const Point p1, const Point p2) : p1(p1), p2(p2) {}

    Point calcProjectionPoint(const Point p) const {
        Vector base = p2 - p1;
        Vector hypo = p - p1;

        // 射影点からp1までの距離
        const double distance = calcDotProduct(hypo, base) / base.norm();

        return p1 + base * distance / base.norm();
    }

    Point calcReflectionPoint(const Point p) const {
        const Point projectionPoint = calcProjectionPoint(p);

        return p + (projectionPoint - p) * 2;
    }
};


typedef Line Segment;


SegmentPointRelation calcRelation(const Segment segment, const Point point) {
    const double crossProduct = calcCrossProduct(segment.p2 - segment.p1, point - segment.p1);

    if (std::abs(crossProduct) < EPS) {
        const double segmentNorm = (segment.p2 - segment.p1).norm();
        const double norm1 = (segment.p1 - point).norm();
        const double norm2 = (segment.p2 - point).norm();
        if (std::abs(segmentNorm - norm1 - norm2) < EPS) {
            return SegmentPointRelation::ON_SEGMENT;
        } else if (norm1 > norm2) {
            return SegmentPointRelation::ONLINE_FRONT;
        } else {
            return SegmentPointRelation::ONLINE_BACK;
        }
    } else if (crossProduct > 0) {
        return SegmentPointRelation::COUNTER_CLOCKWISE;
    } else {
        return SegmentPointRelation::CLOCKWISE;
    }
}


bool isIntersect(const Segment s1, const Segment s2) {
    // 線分が交差する場合はTrueを返す。
    const double crossProduct1 = calcCrossProduct(s1.p2 - s1.p1, s2.p1 - s1.p1);
    const double crossProduct2 = calcCrossProduct(s1.p2 - s1.p1, s2.p2 - s1.p1);

    const double crossProduct3 = calcCrossProduct(s2.p2 - s2.p1, s1.p1 - s2.p1);
    const double crossProduct4 = calcCrossProduct(s2.p2 - s2.p1, s1.p2 - s2.p1);

    return (crossProduct1 * crossProduct2 < 0) && (crossProduct3 * crossProduct4 < 0);
}


double calcDistance(const Line l, const Point p) {
    const Vector a = l.p2 - l.p1;
    const Vector b = p - l.p1;
    return std::abs(calcCrossProduct(a, b) / a.norm());
}


double calcDistanceSP(const Segment s, const Point p) {
    if (calcDotProduct(s.p2 - s.p1, p - s.p1) < 0) {
        return calcDistance(s.p1, p);
    } else if (calcDotProduct(s.p1 - s.p2, p - s.p2) < 0) {
        return calcDistance(s.p2, p);
    } else {
        return calcDistance(s, p);
    }
}


double calcDistance(const Segment s1, const Segment s2) {
    if (isIntersect(s1, s2)) return 0.0;

    const double distance = std::min(
        std::min(calcDistanceSP(s1, s2.p1), calcDistanceSP(s1, s2.p2)),
        std::min(calcDistanceSP(s2, s1.p1), calcDistanceSP(s2, s1.p2))
    );
    return distance;
}


int main() {
    int x0, y0, x1, y1;
    std::cin >> x0 >> y0 >> x1 >> y1;
    const Segment segment = Segment(Point(x0, y0), Point(x1, y1));

    int queryNum;
    std::cin >> queryNum;
    assert(1 <= queryNum && queryNum <= std::pow(10,3));

    for (int _ = 0; _ < queryNum; _++) {
        double x, y;
        std::cin >> x >> y;

        const auto relation = calcRelation(segment, Point(x, y));
        if (relation == SegmentPointRelation::COUNTER_CLOCKWISE) {
            std::cout << "COUNTER_CLOCKWISE" << std::endl;
        } else if (relation == SegmentPointRelation::CLOCKWISE) {
            std::cout << "CLOCKWISE" << std::endl;
        } else if (relation == SegmentPointRelation::ONLINE_BACK) {
            std::cout << "ONLINE_BACK" << std::endl;
        } else if (relation == SegmentPointRelation::ONLINE_FRONT) {
            std::cout << "ONLINE_FRONT" << std::endl;
        } else if (relation == SegmentPointRelation::ON_SEGMENT) {
            std::cout << "ON_SEGMENT" << std::endl;
        } else {
            assert("Invalid relation.");
        }
    }

    return 0;
}

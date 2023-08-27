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


class LineCoefficients {
public:
    // a*x + b*y + c = 0としたときのa,b,c
    const double a, b, c;
    LineCoefficients(const double a, const double b, const double c): a(a), b(b), c(c) {}
};


class Line {
public:
    const Point p1, p2;

    Line(const Point p1, const Point p2) : p1(p1), p2(p2) {}

    double getGradient() const {
        return (p2.y - p1.y) / (p2.x - p1.x);
    }

    double getIntercept() const {
        const double gradient = getGradient();
        const double intercept = p1.y - gradient * p1.x;
        return intercept;
    }

    LineCoefficients getCoefficients() const {
        // a*x + b*y + c = 0としたときのa,b,cを返す

        double a, b, c;
        if (std::abs(p1.x - p2.x) < EPS) {
            a = 1, b = 0, c = -p1.x;
        } else {
            a = getGradient(), b = -1, c = getIntercept();
        }
        return LineCoefficients(a, b, c);
    }

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
    const SegmentPointRelation relation1 = calcRelation(s1, s2.p1);
    const SegmentPointRelation relation2 = calcRelation(s1, s2.p2);
    const SegmentPointRelation relation3 = calcRelation(s2, s1.p1);
    const SegmentPointRelation relation4 = calcRelation(s2, s1.p2);

    const bool s1Relation = (
        (relation1 == SegmentPointRelation::COUNTER_CLOCKWISE && relation2 == SegmentPointRelation::CLOCKWISE)
        || (relation1 == SegmentPointRelation::CLOCKWISE && relation2 == SegmentPointRelation::COUNTER_CLOCKWISE)
    );

    const bool s2Relation = (
        (relation3 == SegmentPointRelation::COUNTER_CLOCKWISE && relation4 == SegmentPointRelation::CLOCKWISE)
        || (relation3 == SegmentPointRelation::CLOCKWISE && relation4 == SegmentPointRelation::COUNTER_CLOCKWISE)
    );

    const bool isOnSegment = (
        relation1 == SegmentPointRelation::ON_SEGMENT
        || relation2 == SegmentPointRelation::ON_SEGMENT
        || relation3 == SegmentPointRelation::ON_SEGMENT
        || relation4 == SegmentPointRelation::ON_SEGMENT
    );

    return (s1Relation && s2Relation) || isOnSegment;
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


Point calcCrossPoint(const Line l1, const Line l2) {
    const auto coefficients1 = l1.getCoefficients();
    const double a1 = coefficients1.a;
    const double b1 = coefficients1.b;
    const double c1 = coefficients1.c;

    const auto coefficients2 = l2.getCoefficients();
    const double a2 = coefficients2.a;
    const double b2 = coefficients2.b;
    const double c2 = coefficients2.c;

    return Point(
        (b1*c2 - b2*c1) / (a1*b2 - a2*b1),
        (a2*c1 - a1*c2) / (a1*b2 - a2*b1)
    );
}


int main() {
    int queryNum;
    std::cin >> queryNum;
    assert(1 <= queryNum && queryNum <= std::pow(10,3));

    for (int _ = 0; _ < queryNum; _++) {
        double x0, y0, x1, y1, x2, y2, x3, y3;
        std::cin >> x0 >> y0;
        std::cin >> x1 >> y1;
        std::cin >> x2 >> y2;
        std::cin >> x3 >> y3;

        const Point p0 = Point(x0, y0), p1 = Point(x1, y1), p2 = Point(x2, y2), p3 = Point(x3, y3);
        const Point crossPoint = calcCrossPoint(Segment(p0, p1), Segment(p2, p3));
        printf("%.10f %.10f\n", crossPoint.x, crossPoint.y);
    }

    return 0;
}

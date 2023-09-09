#include<algorithm>
#include<cassert>
#include<cmath>
#include<iostream>
#include<set>
#include<vector>


const double EPS = 1e-10;


class Point {
public:
    Point(const double x, const double y) : x(x), y(y) {}
    Point operator + (const Point p) const {return Point(x + p.x, y + p.y);}
    Point operator - (const Point p) const {return Point(x - p.x, y - p.y);}
    Point operator * (const double a) const {return Point(a*x, a*y);}
    Point operator / (const double a) const {return Point(x/a, y/a);}
    bool operator == (const Point p) const {
        return std::abs(x - p.x) < EPS && std::abs(y - p.y) < EPS;
    }
    bool operator < (const Point p) const {
        if (std::abs(x - p.x) < EPS) {
            return y < p.y;
        }
        return x < p.x;
    }

    double norm() const {
        const double squaredNorm = x*x + y*y;
        return std::sqrt(squaredNorm);
    }

    double getX() const {return x;}
    double getY() const {return y;}

private:
    double x, y;
};


class Line {
public:
    const Point p1, p2;
    Line(const Point p1, const Point p2) : p1(p1), p2(p2) {}
};


typedef Line Segment;


enum class EndPointType {
    BOTTOM = 0,
    LEFT = 1,
    RIGHT = 2,
    TOP = 3
};


class EndPoint {
public:
    EndPoint(const int segmentId, const Point point, const EndPointType type): segmentId(segmentId), point(point), type(type) {}
    bool operator < (const EndPoint p) const {
        if (point.getY() == p.point.getY()) {
            return type < p.getType();
        }
        return point.getY() < p.point.getY();
    }
    EndPointType getType() const {
        return type;
    }
    Point getPoint() const {
        return point;
    }
    int getId() const {
        return segmentId;
    }

private:
    int segmentId;
    Point point;
    EndPointType type;
};


int calcManhattanIntersection(const std::vector<Segment> segments) {
    int segmentNum = segments.size();

    std::vector<EndPoint> endPoints;
    for (int id = 0; id < segmentNum; id++) {
        const Segment segment = segments[id];
        double minX = segment.p1.getX();
        double maxX = segment.p2.getX();
        double minY = segment.p1.getY();
        double maxY = segment.p2.getY();
        if (minX > maxX) std::swap(minX, maxX);
        if (minY > maxY) std::swap(minY, maxY);

        if (minY == maxY) {
            endPoints.push_back(EndPoint(id, Point(minX, minY), EndPointType::LEFT));
            endPoints.push_back(EndPoint(id, Point(maxX, minY), EndPointType::RIGHT));
        } else if (minX == maxX) {
            endPoints.push_back(EndPoint(id, Point(minX, minY), EndPointType::BOTTOM));
            endPoints.push_back(EndPoint(id, Point(minX, maxY), EndPointType::TOP));
        } else {
            assert(false);
        }
    }

    sort(endPoints.begin(), endPoints.end());

    std::set<double> xValues;
    xValues.insert(std::pow(10, 9) + 1);
    int intersectionNum = 0;
    for (int i = 0; i < endPoints.size(); i++) {
        const EndPoint endPoint = endPoints[i];
        if (endPoint.getType() == EndPointType::TOP) {
            xValues.erase(endPoint.getPoint().getX());
        }
        if (endPoint.getType() == EndPointType::BOTTOM) {
            xValues.insert(endPoint.getPoint().getX());
        }
        if (endPoint.getType() == EndPointType::LEFT) {
            const int id = endPoint.getId();
            double left = segments[id].p1.getX();
            double right = segments[id].p2.getX();
            if (left > right) std::swap(left, right);

            for (auto it = xValues.lower_bound(left); it != xValues.upper_bound(right); ++it) {
                intersectionNum++;
            }
        }
    }

    return intersectionNum;
}


int main() {
    int segmentNum;
    std::cin >> segmentNum;

    std::vector<Segment> segments;
    for (int i = 0; i < segmentNum; i++) {
        double x1, y1, x2, y2;
        std::cin >> x1 >> y1 >> x2 >> y2;
        segments.push_back(Segment(Point(x1, y1), Point(x2, y2)));
    }

    const int intersectionNum = calcManhattanIntersection(segments);

    // 結果表示
    std::cout << intersectionNum << std::endl;

    return 0;
}

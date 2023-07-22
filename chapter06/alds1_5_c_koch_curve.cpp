#include<iostream>
#include<math.h>
#include<vector>


class Point2D {
public:
    Point2D(const double x, const double y) : x(x), y(y) {}
    void print() const {
        printf("%.8f %.8f\n", x, y);
    }
    const double x, y;
};


class KochPoints {
public:
    KochPoints(const Point2D s, const Point2D t, const Point2D u) : s(s), t(t), u(u) {}
    const Point2D s, t, u;
};


KochPoints calcKochPoints(const Point2D p1, const Point2D p2) {
    const Point2D s = Point2D((2 * p1.x + 1 * p2.x) / 3, (2 * p1.y + 1 * p2.y) / 3);
    const Point2D t = Point2D((1 * p1.x + 2 * p2.x) / 3, (1 * p1.y + 2 * p2.y) / 3);

    const double theta = M_PI * 60.0 / 180.0;
    const double ux = s.x + (t.x - s.x) * cos(theta) - (t.y - s.y) * sin(theta);
    const double uy = s.y + (t.x - s.x) * sin(theta) + (t.y - s.y) * cos(theta);

    return KochPoints(s, t, Point2D(ux, uy));
}


void printKochPoints(const int d, const Point2D p1, const Point2D p2) {
    if (d <= 0) return;

    KochPoints p = calcKochPoints(p1, p2);

    printKochPoints(d-1, p1, p.s);
    p.s.print();
    printKochPoints(d-1, p.s, p.u);
    p.u.print();
    printKochPoints(d-1, p.u, p.t);
    p.t.print();
    printKochPoints(d-1, p.t, p2);
}

int main() {
    // 標準入力からのデータ取得
    int n;
    std::cin >> n;
    if (!(0 <= n && n <= 6)) {
        std::cerr << "n is invalid." << std::endl;
        exit(EXIT_FAILURE);
    }

    // 結果
    const Point2D p1 = Point2D(0, 0), p2 = Point2D(100, 0);
    p1.print();
    printKochPoints(n, p1, p2);
    p2.print();

    return 0;
}

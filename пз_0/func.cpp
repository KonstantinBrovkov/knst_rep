#include "func.h"
#include <cmath>
#include <iostream>
using namespace std;

const double DFC = 1e-5;
double pi = 3.14159265358979323846;

bool equal(double a, double b) {
    return fabs(a - b) < DFC;
}

void readPoint(Point& p) {
    cin >> p.x >> p.y;
}

void printPoint(const Point& p) {
    cout << "(" << p.x << ", " << p.y << ")";
}

void readCircle(Circle& c) {
    readPoint(c.center);
    cin >> c.radius;
}

void printCircle(const Circle& c) {
    cout << "Center: ";
    printPoint(c.center);
    cout << ", Radius: " << c.radius;
}

double circleLength(const Circle& c) {
    return 2 * pi * c.radius;
}

double circleArea(const Circle& c) {
    return pi * c.radius * c.radius;
}

void readSquare(Square& s) {
    readPoint(s.topLeft);
    cin >> s.side;
}

void printSquare(const Square& s) {
    cout << "Top-Left: ";
    printPoint(s.topLeft);
    cout << ", Side: " << s.side;
}

double squarePerimeter(const Square& s) {
    return 4 * s.side;
}

double squareArea(const Square& s) {
    return s.side * s.side;
}

bool isPointInCircle(const Point& p, const Circle& c) {
    double dx = p.x - c.center.x;
    double dy = p.y - c.center.y;
    return dx*dx + dy*dy < c.radius*c.radius - DFC;
}

bool isPointInSquare(const Point& p, const Square& s) {
    return p.x > s.topLeft.x + DFC &&
           p.x < s.topLeft.x + s.side - DFC &&
           p.y < s.topLeft.y - DFC &&
           p.y > s.topLeft.y - s.side + DFC;
}

bool isPointOnCircle(const Point& p, const Circle& c) {
    double dx = p.x - c.center.x;
    double dy = p.y - c.center.y;
    return equal(dx*dx + dy*dy, c.radius*c.radius);
}

bool isPointOnSquare(const Point& p, const Square& s) {
    bool onVertical = (equal(p.x, s.topLeft.x) || equal(p.x, s.topLeft.x + s.side)) &&
                      p.y <= s.topLeft.y + DFC && p.y >= s.topLeft.y - s.side - DFC;
    bool onHorizontal = (equal(p.y, s.topLeft.y) || equal(p.y, s.topLeft.y - s.side)) &&
                        p.x >= s.topLeft.x - DFC && p.x <= s.topLeft.x + s.side + DFC;
    return onVertical || onHorizontal;
}

bool doCirclesIntersect(const Circle& c1, const Circle& c2) {
    double dx = c1.center.x - c2.center.x;
    double dy = c1.center.y - c2.center.y;
    double d = sqrt(dx*dx + dy*dy);
    return d < c1.radius + c2.radius + DFC && 
           d > fabs(c1.radius - c2.radius) - DFC;
}

bool doSquaresIntersect(const Square& s1, const Square& s2) {
    bool xOverlap = s1.topLeft.x < s2.topLeft.x + s2.side + DFC &&
                    s2.topLeft.x < s1.topLeft.x + s1.side + DFC;
    bool yOverlap = s1.topLeft.y > s2.topLeft.y - s2.side - DFC &&
                    s2.topLeft.y > s1.topLeft.y - s1.side - DFC;
    return xOverlap && yOverlap;
}

bool doCircleAndSquareIntersect(const Circle& c, const Square& s) {
    // Проверка пересечения с углами квадрата
    Point corners[4] = {
        {s.topLeft.x, s.topLeft.y},
        {s.topLeft.x + s.side, s.topLeft.y},
        {s.topLeft.x, s.topLeft.y - s.side},
        {s.topLeft.x + s.side, s.topLeft.y - s.side}
    };
    for (const Point& corner : corners) {
        if (isPointOnCircle(corner, c) || isPointInCircle(corner, c)) return true;
    }

    // Проверка пересечения с ребрами квадрата
    Point edges[4][2] = {
        {corners[0], corners[1]}, // Верхнее
        {corners[0], corners[2]}, // Левое
        {corners[1], corners[3]}, // Правое
        {corners[2], corners[3]}  // Нижнее
    };
    for (auto& edge : edges) {
        Point A = edge[0], B = edge[1];
        // Проекция центра на прямую
        double t = ((c.center.x - A.x)*(B.x - A.x) + (c.center.y - A.y)*(B.y - A.y)) /
                   ((B.x - A.x)*(B.x - A.x) + (B.y - A.y)*(B.y - A.y));
        t = max(0.0, min(1.0, t));
        Point proj = {
            A.x + t*(B.x - A.x),
            A.y + t*(B.y - A.y)
        };
        double dx = proj.x - c.center.x;
        double dy = proj.y - c.center.y;
        if (dx*dx + dy*dy <= c.radius*c.radius + DFC) return true;
    }

    return false;
}

bool isCircleInCircle(const Circle& c1, const Circle& c2) {
    double dx = c1.center.x - c2.center.x;
    double dy = c1.center.y - c2.center.y;
    double d = sqrt(dx*dx + dy*dy);
    return d + c1.radius < c2.radius + DFC;
}

bool isSquareInSquare(const Square& s1, const Square& s2) {
    return s1.topLeft.x >= s2.topLeft.x - DFC &&
           s1.topLeft.x + s1.side <= s2.topLeft.x + s2.side + DFC &&
           s1.topLeft.y <= s2.topLeft.y + DFC &&
           s1.topLeft.y - s1.side >= s2.topLeft.y - s2.side - DFC;
}

bool isSquareInCircle(const Square& s, const Circle& c) {
    Point corners[4] = {
        {s.topLeft.x, s.topLeft.y},
        {s.topLeft.x + s.side, s.topLeft.y},
        {s.topLeft.x, s.topLeft.y - s.side},
        {s.topLeft.x + s.side, s.topLeft.y - s.side}
    };
    for (const Point& corner : corners) {
        if (!isPointInCircle(corner, c)) return false;
    }
    return true;
}

bool isCircleInSquare(const Circle& c, const Square& s) {
    Point expandedTL = {s.topLeft.x + c.radius, s.topLeft.y - c.radius};
    Point expandedBR = {s.topLeft.x + s.side - c.radius, s.topLeft.y - s.side + c.radius};
    return c.center.x >= expandedTL.x - DFC &&
           c.center.x <= expandedBR.x + DFC &&
           c.center.y <= expandedTL.y + DFC &&
           c.center.y >= expandedBR.y - DFC;
}
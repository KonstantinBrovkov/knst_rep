#include "func.h"
#include <iostream>

using namespace std;

int main() {
    Point p;
    cout << "Enter point (x y): ";
    readPoint(p);

    Circle c;
    cout << "Enter circle (x y radius): ";
    readCircle(c);

    Square s;
    cout << "Enter square (x y side): ";
    readSquare(s);

    cout << "\nPoint: ";
    printPoint(p);
    cout << "\nCircle: ";
    printCircle(c);
    cout << "\nSquare: ";
    printSquare(s);

    cout << "\n\nCircle length: " << circleLength(c);
    cout << "\nCircle area: " << circleArea(c);
    cout << "\nSquare perimeter: " << squarePerimeter(s);
    cout << "\nSquare area: " << squareArea(s);

    cout << "\n\nPoint in circle: " << isPointInCircle(p, c);
    cout << "\nPoint in square: " << isPointInSquare(p, s);
    cout << "\nPoint on circle: " << isPointOnCircle(p, c);
    cout << "\nPoint on square: " << isPointOnSquare(p, s);

    Circle c2;
    cout << "\n\nEnter second circle (x y radius): ";
    readCircle(c2);
    cout << "Circles intersect: " << doCirclesIntersect(c, c2);

    Square s2;
    cout << "\nEnter second square (x y side): ";
    readSquare(s2);
    cout << "Squares intersect: " << doSquaresIntersect(s, s2);
    cout << "\nCircle and square intersect: " << doCircleAndSquareIntersect(c, s);

    cout << "\n\nCircle in circle: " << isCircleInCircle(c, c2);
    cout << "\nSquare in square: " << isSquareInSquare(s, s2);
    cout << "\nSquare in circle: " << isSquareInCircle(s, c);
    cout << "\nCircle in square: " << isCircleInSquare(c, s);

    return 0;
}
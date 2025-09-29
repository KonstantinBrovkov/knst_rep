#ifndef STRUCTS_H
#define STRUCTS_H

struct Point {
    double x, y;
};

struct Circle {
    Point center;
    double radius;
};

struct Square {
    Point topLeft;
    double side;
};

#endif
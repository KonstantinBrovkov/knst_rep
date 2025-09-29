#ifndef FUNC_H
#define FUNC_H

#include "structs.h"

// Точка
void readPoint(Point& p);
void printPoint(const Point& p);

// Круг
void readCircle(Circle& c);
void printCircle(const Circle& c);
double circleLength(const Circle& c);
double circleArea(const Circle& c);

// Квадрат
void readSquare(Square& s);
void printSquare(const Square& s);
double squarePerimeter(const Square& s);
double squareArea(const Square& s);

// Принадлежность точки фигуре
bool isPointInCircle(const Point& p, const Circle& c);
bool isPointInSquare(const Point& p, const Square& s);

// Точка на контуре
bool isPointOnCircle(const Point& p, const Circle& c);
bool isPointOnSquare(const Point& p, const Square& s);

// Пересечение фигур
bool doCirclesIntersect(const Circle& c1, const Circle& c2);
bool doSquaresIntersect(const Square& s1, const Square& s2);
bool doCircleAndSquareIntersect(const Circle& c, const Square& s);

// Принадлежность фигуры
bool isCircleInCircle(const Circle& c1, const Circle& c2);
bool isSquareInSquare(const Square& s1, const Square& s2);
bool isSquareInCircle(const Square& s, const Circle& c);
bool isCircleInSquare(const Circle& c, const Square& s);

#endif
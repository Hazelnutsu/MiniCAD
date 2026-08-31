#pragma once
#include "minicad/point.hpp"


namespace minicad{
    struct Vector2D{
        double x;
        double y;
    };
    Vector2D vectorBetween(const Point2D& from, const Point2D& to);
    Vector2D operator+(const Vector2D& a, const Vector2D& b);
    Vector2D operator-(const Vector2D& a, const Vector2D& b);
    Vector2D operator*(const Vector2D& v, double scalar);
    double magnitude(const Vector2D& v);
    double dot(const Vector2D& a, const Vector2D& b);
    Vector2D normalize(const Vector2D& v);
}
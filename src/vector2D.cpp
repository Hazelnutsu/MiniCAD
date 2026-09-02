#include "minicad/vector2D.hpp"
#include <cmath>

namespace minicad{
    Vector2D vectorBetween(const Point2D& from, const Point2D& to) {
        double dx = to.x - from.x;
        double dy = to.y - from.y;
        Vector2D v{dx, dy};
        return v;
    }

    Vector2D operator+(const Vector2D& a, const Vector2D& b) {
        double x = a.x + b.x;
        double y = a.y + b.y;
        Vector2D v{x, y};
        return v;
    }

    Vector2D operator-(const Vector2D& a, const Vector2D& b) {
        double x = a.x - b.x;
        double y = a.y - b.y;
        Vector2D v{x, y};
        return v;
    }

    Vector2D operator*(const Vector2D& v, double scalar) {
        return Vector2D{v.x * scalar, v.y * scalar};
    }

    double magnitude(const Vector2D& v) {
        double mag = v.x * v.x + v.y * v.y;
        return std::sqrt(mag);
    }

    double dot(const Vector2D& a, const Vector2D& b) {
        return a.x * b.x + a.y * b.y;
    }
    
    Vector2D normalize(const Vector2D& v) {
        if(v.x == 0 && v.y == 0) {
            return v;
        }
        double mag = magnitude(v);
        return Vector2D {v.x / mag , v.y / mag};
    }
}
#include "minicad/point.hpp"
#include <cmath>

namespace minicad {

    double distance(const Point2D& a, const Point2D& b) {
        double dx = a.x - b.x;
        double dy = a.y - b.y;
        return std::sqrt(dx*dx + dy*dy);
    }
    bool approximatelyEqual(const Point2D& a, const Point2D& b) {
        return approximatelyEqual(a.x, b.x, EPSILON) && approximatelyEqual(a.y, b.y, EPSILON);
    }
    
}
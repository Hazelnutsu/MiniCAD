#include "minicad/point.hpp"
#include "minicad/numeric.hpp"
#include <cmath>

namespace minicad {
    //calculates distance between 2 points
    double distance(const Point2D& a, const Point2D& b) {
        double dx = a.x - b.x;
        double dy = a.y - b.y;
        return std::sqrt(dx*dx + dy*dy);
    }
    //checks whether 2 points are equal with float tolerance
    bool approximatelyEqual(const Point2D& a, const Point2D& b) {
        return approximatelyEqual(a.x, b.x, epsilon) && approximatelyEqual(a.y, b.y, epsilon);
    }
    
}
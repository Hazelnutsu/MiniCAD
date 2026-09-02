#pragma once
#include "minicad/point.hpp"

namespace minicad {

    enum class Orientation {
        Clockwise,
        Counterclockwise,
        Collinear
    };

    class Segment {
        public: 
            Segment(const Point2D& start, const Point2D& end);
            double length() const;
            Point2D midpoint() const;
            Orientation orientation(const Point2D& p) const;

        private:
            Point2D start_;
            Point2D end_;
    };
}
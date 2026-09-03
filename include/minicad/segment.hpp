#pragma once
#include "minicad/point.hpp"
#include <optional>

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
            bool contains(const Point2D& p) const;
            const Point2D& start() const;
            const Point2D& end() const;

        private:
            Point2D start_;
            Point2D end_;
    };
    std::optional<Point2D> intersection(const Segment& a, const Segment& b);
}
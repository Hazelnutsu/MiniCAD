#pragma once
#include "minicad/point.hpp"

namespace minicad{

    class Segment{
        public: 
            Segment(const Point2D& start, const Point2D& end);
            double length() const;
            Point2D midpoint() const;

        private:
            Point2D start_;
            Point2D end_;
    };
}
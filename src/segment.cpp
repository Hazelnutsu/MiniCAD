#include "minicad/segment.hpp"
#include "minicad/vector2D.hpp"
#include <algorithm>

namespace minicad {

    Segment::Segment(const Point2D& start, const Point2D& end)
        : start_(start),
          end_(end)
    {
    }

    double Segment::length() const {

        return distance(start_, end_);
    }

    Point2D Segment::midpoint() const {

        double midx = (start_.x + end_.x) / 2;
        double midy = (start_.y + end_.y) / 2;

        return Point2D{midx, midy};
    }

    Orientation Segment:: orientation(const Point2D& p) const {

        Vector2D ab = vectorBetween(start_, end_);
        Vector2D ap = vectorBetween(start_, p);
        double cross = ab.x * ap.y - ab.y * ap.x;

        if(cross > 0) {
            return Orientation::Counterclockwise;
        }

        if(cross < 0) {
            return Orientation::Clockwise;
        }

        return Orientation::Collinear;
    }

}
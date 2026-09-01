#include "minicad/segment.hpp"

namespace minicad {

    Segment::Segment(const Point2D& start, const Point2D& end)
        : start_(start),
          end_(end)
    {
    }

    double Segment::length() const {

        return distance(start_, end_);
    }

    Point2D Segment::midpoint() const{

        double midx = (start_.x + end_.x) / 2;
        double midy = (start_.y + end_.y) / 2;

        return Point2D{midx, midy};
    }

}
#include "minicad/segment.hpp"
#include "minicad/vector2D.hpp"
#include "minicad/numeric.hpp"
#include <cmath>
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
    
    const Point2D& Segment::start() const {
        return start_;
    }
    
    const Point2D& Segment::end() const {
        return end_;
    }

    Orientation Segment:: orientation(const Point2D& p) const {

        Vector2D ab = vectorBetween(start_, end_);
        Vector2D ap = vectorBetween(start_, p);
        double cross = ab.x * ap.y - ab.y * ap.x;

        if(std::abs(cross) <= epsilon) {
            return Orientation::Collinear;
        }

        if(cross > 0) {
            return Orientation::Counterclockwise;
        }

        return Orientation::Clockwise;
    }
    
    bool Segment::contains(const Point2D& p) const {
        
        if(orientation(p) == Orientation::Collinear) {

            double minX = std::min(start_.x, end_.x);
            double maxX = std::max(start_.x, end_.x);
            double minY = std::min(start_.y, end_.y);
            double maxY = std::max(start_.y, end_.y);

            if(p.x >= minX - epsilon && p.x <= maxX + epsilon &&
                 p.y >= minY - epsilon && p.y <= maxY + epsilon) {
                return true;
            }
        }
        return false;
    }

    bool intersects(const Segment& a, const Segment& b) {
        const bool hasEndpointContact =
            a.contains(b.start()) ||
            a.contains(b.end()) ||
            b.contains(a.start()) ||
            b.contains(a.end());

        if (hasEndpointContact) {
            return true;
        }

        const Orientation aStartRelativeToB = b.orientation(a.start());
        const Orientation aEndRelativeToB = b.orientation(a.end());
        const Orientation bStartRelativeToA = a.orientation(b.start());
        const Orientation bEndRelativeToA = a.orientation(b.end());

        const auto haveOppositeOrientations = [](const Orientation first,
                                                  const Orientation second) {
            return (first == Orientation::Clockwise &&
                    second == Orientation::Counterclockwise) ||
                   (first == Orientation::Counterclockwise &&
                    second == Orientation::Clockwise);
        };

        return haveOppositeOrientations(aStartRelativeToB, aEndRelativeToB) &&
               haveOppositeOrientations(bStartRelativeToA, bEndRelativeToA);
    }

}

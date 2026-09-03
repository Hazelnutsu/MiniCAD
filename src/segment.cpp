#include "minicad/segment.hpp"
#include "minicad/vector2D.hpp"
#include "minicad/numeric.hpp"
#include <cmath>
#include <algorithm>
#include <optional>

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
        double crossVal = cross(ab, ap);

        if(std::abs(crossVal) <= epsilon) {
            return Orientation::Collinear;
        }

        if(crossVal > 0) {
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

    std::optional<Point2D> intersection(const Segment& a, const Segment& b) {
        const Point2D& p = a.start();
        const Point2D& q = b.start();

        Vector2D r = vectorBetween(a.start(), a.end());
        Vector2D s = vectorBetween(b.start(), b.end());
        Vector2D pq = vectorBetween(p, q);

        double denominator = cross(r, s);

        if(approximatelyEqual(denominator, 0.0, epsilon)) {
            if(!approximatelyEqual(cross(pq, r), 0.0, epsilon)) {
                //parallel no
                return std::nullopt;
            }
            //collinear
            return std::nullopt;
        }

        double t = cross(pq, s) / denominator;
        double u = cross(pq, r) / denominator;


        if(t >= -epsilon && t <= 1 + epsilon && u >= -epsilon && u <= 1 + epsilon) {
            Point2D intersectionPoint{p.x + t * r.x, p.y + t * r.y};
            return intersectionPoint;
        }

        return std::nullopt;
    }

}

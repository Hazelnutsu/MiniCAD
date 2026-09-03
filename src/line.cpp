#include "minicad/line.hpp"
#include "minicad/numeric.hpp"

namespace minicad {
    Line::Line(const Point2D& point, const Vector2D& direction)
        : point_(point) ,
          direction_(direction)
    {
    }

    const Point2D& Line::point() const {
        return point_;
    }

    const Vector2D& Line::direction() const {
        return direction_;
    }

    std::optional<Point2D> intersection(const Line& a, const Line& b) {
        const Point2D& p = a.point();
        const Point2D& q = b.point();

        const Vector2D& r = a.direction();
        const Vector2D& s = b.direction();

        Vector2D pq = vectorBetween(p, q);

        double denominator = cross(r,s);

        if(approximatelyEqual(denominator, 0.0, epsilon)) {
            return std::nullopt;
        }

        double t = cross(pq, s) / denominator;
        Point2D intersectionPoint{p.x + t * r.x, p.y + t * r.y};

        return intersectionPoint;
    }
}
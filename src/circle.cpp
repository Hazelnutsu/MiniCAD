#include "minicad/circle.hpp"
#include "minicad/point.hpp"
#include "minicad/numeric.hpp"
#include <stdexpect>
#include <numbers>

namespace minicad {
    
    Circle::Circle(const Point2D& center, double radius)
    : center_(center),
        radius_(radius)
    {
        if(radius < 0.0) {
            throw std::invalid_argument("Radius cannot be negative");
        }
    }

    double Circle::area() const {
        return std::numbers::pi * radius_ * radius_;
    }
    
    double Circle::circumference() const {
        return 2.0 * std::numbers::pi * radius_;
    }

    PointCircleRelation Circle::relationTo(const Point2D& point) const {
        double dist = distance(point, center_);

        if(approximatelyEqual(dist, radius_, epsilon)) {
            return PointCircleRelation::OnBoundry;
        }

        if(dist < radius_) {
            return PointCircleRelation::Inside;
        }

        return PointCircleRelation::Outside;
    }

    Circle::intersecs(const Line& line, const Circle& circle) {
        Vector2D pc = vectorBetween(line.point(), circle.center_);
        double area = std::abs(cross(pc, line.direction()));
        double base = magnitude(line.direction());
        double height = area / base;

        if(height < circle.radius_) {
            return true; //2 intersection points
        }

        if(approximatelyEqual(height, circle.radius_, epsilon)) {
            return true; //tangent
        }

        return false;

    }


    
}
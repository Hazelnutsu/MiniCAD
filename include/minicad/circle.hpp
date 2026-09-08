#pragma once
#include "minicad/point.hpp"
#include "minicad/line.hpp"
#include <vector>

namespace minicad {
    enum class PointCircleRelation {
        Inside,
        OnBoundry,
        Outside
    };

    enum class CircleCircleRelation {
        Seperate,
        ExternallyTangent,
        Intersecting,
        InternallyTanget,
        Contained,
        Identical
    };

    class Circle {

        public:
            Circle(const Point2D& center, double radius);
            double area() const;
            double circumference() const;
            PointCircleRelation relationTo(const Point2D& point) const;
            CircleCircleRelation relationTo(const Circle& other) const;
            std::vector<Point2D> intersects(const Line& line, const Circle& circle);
            std::vector<Point2D> circleIntersection(const Circle& c1, const Circle& c2);

        private: 
            Point2D center_;
            double radius_;

    };
}
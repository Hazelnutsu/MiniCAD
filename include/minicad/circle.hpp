#pragma once
#include "minicad/point.hpp"

namespace minicad {
    enum class PointCircleRelation {
        Inside,
        OnBoundry,
        Outside
    };

    class Circle {

        public:
            Circle(const Point2D& center, double radius);
            double area() const;
            double circumference() const;
            PointCircleRelation relationTo(const Point2D& point) const;
            bool intersects(const Line& line, const Circle& circle);

        private: 
            Point2D center_;
            double radius_;

    };
}
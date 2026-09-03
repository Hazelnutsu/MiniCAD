#pragma once
#include "minicad/point.hpp"
#include "minicad/vector2D.hpp"
#include <optional>

namespace minicad {

    class Line {
        public:
            Line(const Point2D& point, const Vector2D& direction);
            const Point2D& point() const;
            const Vector2D& direction() const;
            
        private:
            Point2D point_;
            Vector2D direction_;
    };
    std::optional<Point2D> intersection(const Line& a, const Line& b);
}
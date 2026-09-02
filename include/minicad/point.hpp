#pragma once


namespace minicad {
    struct Point2D {
        double x;
        double y;
    };

    double distance(const Point2D& a, const Point2D& b);
    bool approximatelyEqual(const Point2D& a, const Point2D& b);
}
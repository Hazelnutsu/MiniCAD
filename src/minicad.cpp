#include "minicad/minicad.hpp"
#include "minicad/point.hpp"

#include <cstddef>
#include <iostream>
#include <vector>

namespace minicad {

int run() {
    std::size_t point_count{};
    std::cout << "How many points would you like to enter? ";
    if (!(std::cin >> point_count)) {
        std::cerr << "Invalid point count.\n";
        return 1;
    }

    std::vector<Point> points;
    points.reserve(point_count);

    for (std::size_t index = 0; index < point_count; ++index) {
        Point point;
        std::cout << "Enter x and y for point " << index + 1 << ": ";
        if (!(std::cin >> point.x >> point.y)) {
            std::cerr << "Invalid point coordinates.\n";
            return 1;
        }
        points.push_back(point);
    }

    std::cout << "Points entered:\n";
    for (const Point& point : points) {
        std::cout << "Point: (" << point.x << ", " << point.y << ")\n";
    }
    return 0;
}

}  // namespace minicad

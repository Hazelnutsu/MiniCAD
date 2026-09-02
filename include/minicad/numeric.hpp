#pragma once

namespace minicad {
    constexpr double EPSILON = 1e-9;

    bool approximatelyEqual(double a, double b, double epsilon);
}
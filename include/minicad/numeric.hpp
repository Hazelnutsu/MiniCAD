#pragma once

namespace minicad {

    constexpr double epsilon = 1e-9;
    bool approximatelyEqual(double a, double b, double epsilon);
}
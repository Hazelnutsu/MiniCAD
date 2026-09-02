#include "minicad/numeric.hpp"
#include <cmath>

namespace minicad{
    
    bool approximatelyEqual(double a, double b, double epsilon) {
        return std::abs(a-b) < epsilon;
    }
}


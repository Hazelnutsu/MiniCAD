#include "minicad/minicad.hpp"
#include "minicad/point.hpp"
#include "minicad/vector2D.hpp"
#include "minicad/numeric.hpp"

#include <cstddef>
#include <iostream>
#include <vector>

namespace minicad {

int run() {
   Vector2D a{2, 3};
    Vector2D b{4, 1};

    Vector2D sum = a + b;
    Vector2D difference = a - b;
    Vector2D scaled = a * 2.0;

    std::cout << "sum: "
          << sum.x << ", " << sum.y << '\n';

    std::cout << "difference: "
          << difference.x << ", " << difference.y << '\n';

    std::cout << "scaled: "
          << scaled.x << ", " << scaled.y << '\n';

    return 0;
}

}  // namespace minicad

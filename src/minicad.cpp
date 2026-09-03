#include "minicad/minicad.hpp"
#include "minicad/point.hpp"
#include "minicad/vector2D.hpp"
#include "minicad/numeric.hpp"
#include "minicad/line.hpp"

#include <cstddef>
#include <iostream>
#include <vector>

namespace minicad {

int run() {
      Point2D p{1,2};
      Vector2D v{3,4};
      Line l{p, v};

    return 0;
}

}  // namespace minicad

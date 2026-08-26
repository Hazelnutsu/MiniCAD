#pragma once

#include <string_view>

namespace minicad {

[[nodiscard]] constexpr std::string_view name() noexcept {
    return "MiniCAD";
}

[[nodiscard]] int run();

}  // namespace minicad

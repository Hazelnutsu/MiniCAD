#include "minicad/numeric.hpp"
#include "minicad/point.hpp"
#include "minicad/vector2D.hpp"

#include <catch2/catch_approx.hpp>
#include <catch2/catch_test_macros.hpp>

using Catch::Approx;

TEST_CASE("distance calculates the distance between two points") {
    const minicad::Point2D a{0.0, 0.0};
    const minicad::Point2D b{3.0, 4.0};

    CHECK(minicad::distance(a, b) == Approx(5.0));
    CHECK(minicad::distance(b, a) == Approx(5.0));
    CHECK(minicad::distance(a, a) == Approx(0.0));
}

TEST_CASE("magnitude calculates a vector's length") {
    CHECK(minicad::magnitude({3.0, 4.0}) == Approx(5.0));
    CHECK(minicad::magnitude({0.0, 0.0}) == Approx(0.0));
}

TEST_CASE("dot calculates the dot product") {
    const minicad::Vector2D a{1.0, 2.0};
    const minicad::Vector2D b{3.0, 4.0};

    CHECK(minicad::dot(a, b) == Approx(11.0));
    CHECK(minicad::dot({1.0, 0.0}, {0.0, 1.0}) == Approx(0.0));
}

TEST_CASE("normalize produces a unit vector") {
    const minicad::Vector2D result = minicad::normalize({3.0, 4.0});

    CHECK(result.x == Approx(0.6));
    CHECK(result.y == Approx(0.8));
    CHECK(minicad::magnitude(result) == Approx(1.0));
}

TEST_CASE("normalizing the zero vector returns the zero vector") {
    const minicad::Vector2D result = minicad::normalize({0.0, 0.0});

    CHECK(result.x == Approx(0.0));
    CHECK(result.y == Approx(0.0));
}

TEST_CASE("approximatelyEqual compares scalar values") {
    CHECK(minicad::approximatelyEqual(
        1.0, 1.0 + minicad::EPSILON / 2.0, minicad::EPSILON));

    CHECK_FALSE(minicad::approximatelyEqual(
        1.0, 1.0 + minicad::EPSILON * 2.0, minicad::EPSILON));
}

TEST_CASE("approximatelyEqual compares points") {
    const minicad::Point2D point{1.0, 2.0};

    CHECK(minicad::approximatelyEqual(
        point,
        {1.0 + minicad::EPSILON / 2.0,
         2.0 - minicad::EPSILON / 2.0}));

    CHECK_FALSE(minicad::approximatelyEqual(
        point,
        {1.0 + minicad::EPSILON * 2.0, 2.0}));
}

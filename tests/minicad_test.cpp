#include "minicad/minicad.hpp"
#include "minicad/numeric.hpp"
#include "minicad/point.hpp"
#include "minicad/segment.hpp"
#include "minicad/vector2D.hpp"
#include "minicad/line.hpp"

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

TEST_CASE("vectorBetween calculates the vector between two points") {
    const minicad::Point2D from{1.0, 2.0};
    const minicad::Point2D to{4.0, 6.0};

    const minicad::Vector2D result = minicad::vectorBetween(from, to);

    CHECK(result.x == Approx(3.0));
    CHECK(result.y == Approx(4.0));
}

TEST_CASE("cross calculates the signed area of two vectors") {
    CHECK(minicad::cross({1.0, 0.0}, {0.0, 1.0}) == Approx(1.0));
    CHECK(minicad::cross({0.0, 1.0}, {1.0, 0.0}) == Approx(-1.0));
    CHECK(minicad::cross({1.0, 2.0}, {2.0, 4.0}) == Approx(0.0));
}

TEST_CASE("vector addition adds corresponding coordinates") {
    const minicad::Vector2D result = minicad::Vector2D{1.0, 2.0}
        + minicad::Vector2D{3.0, 4.0};

    CHECK(result.x == Approx(4.0));
    CHECK(result.y == Approx(6.0));
}

TEST_CASE("vector subtraction subtracts corresponding coordinates") {
    const minicad::Vector2D result = minicad::Vector2D{5.0, 7.0}
        - minicad::Vector2D{2.0, 3.0};

    CHECK(result.x == Approx(3.0));
    CHECK(result.y == Approx(4.0));
}

TEST_CASE("scalar multiplication scales both coordinates") {
    const minicad::Vector2D result = minicad::Vector2D{2.0, -3.0} * 2.5;

    CHECK(result.x == Approx(5.0));
    CHECK(result.y == Approx(-7.5));
}

TEST_CASE("vectorBetween allows a zero-length segment") {
    const minicad::Point2D start{5.0, 5.0};
    const minicad::Point2D end{5.0, 5.0};

    const minicad::Vector2D result =
        minicad::vectorBetween(start, end);

    CHECK(result.x == Approx(0.0));
    CHECK(result.y == Approx(0.0));
    CHECK(minicad::magnitude(result) == Approx(0.0));
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

TEST_CASE("segment length calculates the distance between its endpoints") {
    const minicad::Segment segment{{1.0, 2.0}, {4.0, 6.0}};

    CHECK(segment.length() == Approx(5.0));
}

TEST_CASE("segment midpoint calculates the point halfway between its endpoints") {
    const minicad::Segment segment{{-2.0, 5.0}, {4.0, -1.0}};

    const minicad::Point2D midpoint = segment.midpoint();

    CHECK(midpoint.x == Approx(1.0));
    CHECK(midpoint.y == Approx(2.0));
}

TEST_CASE("segment exposes its start and end points") {
    const minicad::Segment segment{{-1.0, 2.0}, {3.0, 5.0}};

    CHECK(minicad::approximatelyEqual(segment.start(), {-1.0, 2.0}));
    CHECK(minicad::approximatelyEqual(segment.end(), {3.0, 5.0}));
}

TEST_CASE("segment orientation classifies points relative to the segment") {
    const minicad::Segment segment{{0.0, 0.0}, {4.0, 0.0}};

    CHECK(segment.orientation({2.0, 1.0}) ==
          minicad::Orientation::Counterclockwise);
    CHECK(segment.orientation({2.0, -1.0}) ==
          minicad::Orientation::Clockwise);
    CHECK(segment.orientation({2.0, 0.0}) == minicad::Orientation::Collinear);
}

TEST_CASE("segment orientation treats near-collinear points within tolerance as collinear") {
    const minicad::Segment segment{{0.0, 0.0}, {4.0, 0.0}};

    CHECK(segment.orientation({2.0, minicad::epsilon / 8.0}) ==
          minicad::Orientation::Collinear);
    CHECK(segment.orientation({2.0, minicad::epsilon / 2.0}) ==
          minicad::Orientation::Counterclockwise);
    CHECK(segment.orientation({2.0, -minicad::epsilon / 2.0}) ==
          minicad::Orientation::Clockwise);
}

TEST_CASE("segment contains points within endpoint tolerance but rejects points beyond it") {
    const minicad::Segment segment{{0.0, 0.0}, {4.0, 0.0}};

    CHECK(segment.contains({0.0, 0.0}));
    CHECK(segment.contains({2.0, 0.0}));
    CHECK(segment.contains({4.0 + minicad::epsilon / 2.0, 0.0}));
    CHECK_FALSE(segment.contains({4.0 + minicad::epsilon * 2.0, 0.0}));
    CHECK_FALSE(segment.contains({2.0, minicad::epsilon / 2.0}));
}

TEST_CASE("intersection returns the point where segments cross") {
    const minicad::Segment crossingA{{0.0, 0.0}, {4.0, 4.0}};
    const minicad::Segment crossingB{{0.0, 4.0}, {4.0, 0.0}};

    const auto result = minicad::intersection(crossingA, crossingB);

    REQUIRE(result.has_value());
    CHECK(result->x == Approx(2.0));
    CHECK(result->y == Approx(2.0));
}

TEST_CASE("intersection returns no point for disjoint segments") {
    const minicad::Segment disjointA{{0.0, 0.0}, {1.0, 1.0}};
    const minicad::Segment disjointB{{2.0, 0.0}, {3.0, 1.0}};

    CHECK_FALSE(minicad::intersection(disjointA, disjointB).has_value());
}

TEST_CASE("intersection returns a shared endpoint") {
    const minicad::Segment first{{0.0, 0.0}, {4.0, 4.0}};
    const minicad::Segment second{{4.0, 4.0}, {6.0, 2.0}};

    const auto result = minicad::intersection(first, second);

    REQUIRE(result.has_value());
    CHECK(result->x == Approx(4.0));
    CHECK(result->y == Approx(4.0));
}

TEST_CASE("intersection returns no point for parallel or overlapping segments") {
    const minicad::Segment parallelA{{0.0, 0.0}, {4.0, 0.0}};
    const minicad::Segment parallelB{{0.0, 1.0}, {4.0, 1.0}};
    CHECK_FALSE(minicad::intersection(parallelA, parallelB).has_value());

    const minicad::Segment overlappingA{{0.0, 0.0}, {4.0, 4.0}};
    const minicad::Segment overlappingB{{2.0, 2.0}, {6.0, 6.0}};
    CHECK_FALSE(minicad::intersection(overlappingA, overlappingB).has_value());
}

TEST_CASE("approximatelyEqual compares scalar values") {
    CHECK(minicad::approximatelyEqual(
        1.0, 1.0 + minicad::epsilon / 2.0, minicad::epsilon));

    CHECK_FALSE(minicad::approximatelyEqual(
        1.0, 1.0 + minicad::epsilon * 2.0, minicad::epsilon));
}

TEST_CASE("approximatelyEqual compares points") {
    const minicad::Point2D point{1.0, 2.0};

    CHECK(minicad::approximatelyEqual(
        point,
        {1.0 + minicad::epsilon / 2.0,
         2.0 - minicad::epsilon / 2.0}));

    CHECK_FALSE(minicad::approximatelyEqual(
        point,
        {1.0 + minicad::epsilon * 2.0, 2.0}));
}

TEST_CASE("line stores its point and direction") {
    const minicad::Point2D point{1.0, 2.0};
    const minicad::Vector2D direction{3.0, 4.0};
    const minicad::Line line{point, direction};

    CHECK(minicad::approximatelyEqual(line.point(), point));
    CHECK(line.direction().x == Approx(3.0));
    CHECK(line.direction().y == Approx(4.0));
}

TEST_CASE("line intersection returns the intersection of infinite lines") {
    const minicad::Line first{{0.0, 0.0}, {1.0, 1.0}};
    const minicad::Line second{{0.0, 4.0}, {1.0, -1.0}};

    const auto result = minicad::intersection(first, second);

    REQUIRE(result.has_value());
    CHECK(result->x == Approx(2.0));
    CHECK(result->y == Approx(2.0));
}

TEST_CASE("line intersection returns no point for parallel or coincident lines") {
    const minicad::Line parallelA{{0.0, 0.0}, {1.0, 0.0}};
    const minicad::Line parallelB{{0.0, 1.0}, {1.0, 0.0}};
    CHECK_FALSE(minicad::intersection(parallelA, parallelB).has_value());

    const minicad::Line coincidentA{{0.0, 0.0}, {1.0, 0.0}};
    const minicad::Line coincidentB{{2.0, 0.0}, {1.0, 0.0}};
    CHECK_FALSE(minicad::intersection(coincidentA, coincidentB).has_value());
}

TEST_CASE("name identifies the project") {
    CHECK(minicad::name() == "MiniCAD");
}

TEST_CASE("run completes successfully") {
    CHECK(minicad::run() == 0);
}

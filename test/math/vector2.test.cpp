#include "../../src/math/Vector2.h"
#include <catch2/catch.hpp>

TEST_CASE("Vector2 exists", "[Vector2]") {
  Adagio::Vector2u vec{};
  Adagio::Vector2f fvec{};
}

TEST_CASE("Vector2 can be initialized", "[Vector2]") {
  Adagio::Vector2i vec{1, 1};
  Adagio::Vector2f fvec = Adagio::Vector2f();
  REQUIRE(vec.x == 1);
  REQUIRE(vec.y == 1);
  REQUIRE(fvec.x == 0);
  REQUIRE(fvec.y == 0);
}

TEST_CASE("Vector2 can cast between types", "[Vector2]") {
  Adagio::Vector2f fvec{3.141, 2.718};
  auto vec = Adagio::Vector2i(fvec);
  REQUIRE(vec.x == 3);
  REQUIRE(vec.y == 2);
}

TEST_CASE("Vector2 vector arithmetic", "[Vector2]") {
  Adagio::Vector2i vec{1, 2};
  Adagio::Vector2i vec2{3, 4};

  SECTION("Addition") {
    auto vec3 = vec + vec2;
    REQUIRE(vec3.x == 4);
    REQUIRE(vec3.y == 6);
  }

  SECTION("Subtraction") {
    auto vec3 = vec - vec2;
    REQUIRE(vec3.x == -2);
    REQUIRE(vec3.y == -2);
  }

  SECTION("Plus equals") {
    Adagio::Vector2i vec3{0, 0};
    vec3 += vec;
    REQUIRE(vec3.x == 1);
    REQUIRE(vec3.y == 2);
  }

  SECTION("Minus equals") {
    Adagio::Vector2i vec3{0, 0};
    vec3 -= vec;
    REQUIRE(vec3.x == -1);
    REQUIRE(vec3.y == -2);
  }
}

TEST_CASE("Vector2 scalar arithmetic", "[Vector2]") {
  Adagio::Vector2d vec{1, 1};

  SECTION("Scalar multiply") {
    auto vec2 = vec * 5.0;
    REQUIRE(vec2.x == 5.0);
    REQUIRE(vec2.y == 5.0);
  }

  SECTION("Scalar multiply, yoda style") {
    auto vec2 = 5.0 * vec;
    REQUIRE(vec2.x == 5.0);
    REQUIRE(vec2.y == 5.0);
  }

  SECTION("Scalar divide") {
    auto vec2 = vec / 2.0;
    REQUIRE(vec2.x == 0.5);
    REQUIRE(vec2.y == 0.5);
  }

  SECTION("Scalar divide, cursed style") {
    auto vec2 = 2.0 / vec;
    REQUIRE(vec2.x == 2.0);
    REQUIRE(vec2.y == 2.0);
  }
}

TEST_CASE("Vector2 has magnitude", "[Vector2]") {
  Adagio::Vector2i zero{0, 0};
  Adagio::Vector2i vec{5, 12};
  Adagio::Vector2i vec2{3, 4};
  REQUIRE(zero.magnitude() == 0);
  REQUIRE(vec.magnitude() == 13);
  REQUIRE(vec2.magnitude() == 5);
}

TEST_CASE("Vector2 comparison", "[Vector2]") {
  Adagio::Vector2i vec1{0, 0};
  Adagio::Vector2i vec2{0, 0};
  Adagio::Vector2i vec3{100, 100};
  REQUIRE(vec1 == vec2);
  REQUIRE_FALSE(vec1 == vec3);

  REQUIRE(vec1 != vec3);
  REQUIRE_FALSE(vec1 != vec2);
}

TEST_CASE("Vector2 string serialization", "[Vector2]") {
  Adagio::Vector2i vec1{1, 2};
  REQUIRE(vec1.to_string() == "Vector2(1,2)");
}

TEST_CASE("Vector2 normalization", "[Vector2]") {
  Adagio::Vector2d vec1{3, 0};
  auto normalized = vec1.normalized();
  REQUIRE(normalized.x == 1);
  REQUIRE(normalized.y == 0);

  vec1.x = 123;
  vec1.y = 456;
  REQUIRE(vec1.normalized().magnitude() == 1);
}

TEST_CASE("Vector2 floor", "[Vector2]") {
  Adagio::Vector2d vec{3.141, 2.718};
  auto floored = vec.floor();
  REQUIRE(floored.x == 3);
  REQUIRE(floored.y == 2);
}

TEST_CASE("Vector2 clamp", "[Vector2]") {
  Adagio::Vector2i vec{0, 0};
  Adagio::Vector2i lower{-10, -10};
  Adagio::Vector2i upper{10, 10};

  vec.clamp(lower, upper);
  REQUIRE(vec.x == 0);
  REQUIRE(vec.y == 0);

  vec.x = -11;
  vec.y = -100;
  vec.clamp(lower, upper);
  REQUIRE(vec.x == -10);
  REQUIRE(vec.y == -10);

  vec.x = 11;
  vec.y = 100;
  vec.clamp(lower, upper);
  REQUIRE(vec.x == 10);
  REQUIRE(vec.y == 10);
}

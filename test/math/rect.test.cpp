#include "../../src/math/Rect.h"
#include <catch2/catch.hpp>

TEST_CASE("Rect exists", "[Rect]") { Adagio::Rect<int> rect; }

TEST_CASE("Rect initialization", "[Rect]") {
  Adagio::Rect<int> rect(0, 0, 1, 1);
  REQUIRE(rect.position.x == 0);
  REQUIRE(rect.position.y == 0);
  REQUIRE(rect.size.x == 1);
  REQUIRE(rect.size.y == 1);
  Adagio::Rect<double> drect(Adagio::Vector2d(0, 1), Adagio::Vector2d(2, 3));
  REQUIRE(drect.position == Adagio::Vector2d(0, 1));
  REQUIRE(drect.size == Adagio::Vector2d(2, 3));
  Adagio::Rect<int> copy(drect);
  REQUIRE(copy.position == Adagio::Vector2i(0, 1));
  REQUIRE(copy.size == Adagio::Vector2i(2, 3));
}

TEST_CASE("Rect accessor methods", "[Rect]") {
  Adagio::Rect<int> rect(1, 2, 3, 4);
  REQUIRE(rect.x() == 1);
  REQUIRE(rect.y() == 2);
  REQUIRE(rect.width() == 3);
  REQUIRE(rect.height() == 4);
}

TEST_CASE("Rect can get center point", "[Rect]") {
  Adagio::Rect<double> rect(0, 0, 4, 4);
  auto center = rect.center();
  REQUIRE(center.x == 2);
  REQUIRE(center.y == 2);
}

TEST_CASE("Rect can get list of corners", "[Rect]") {
  Adagio::Rect<int> rect(0, 0, 1, 1);
  auto corners = rect.corners();
  REQUIRE(corners[0] == Adagio::Vector2i(0, 0));
  REQUIRE(corners[1] == Adagio::Vector2i(1, 0));
  REQUIRE(corners[2] == Adagio::Vector2i(0, 1));
  REQUIRE(corners[3] == Adagio::Vector2i(1, 1));
}

TEST_CASE("Rect can detect if point is contained within", "[Rect]") {
  Adagio::Rect<int> rect(0, 0, 10, 10);
  Adagio::Vector2i point{5, 5};
  REQUIRE(rect.contains(point));
  point.x = -1;
  point.y = -1;
  REQUIRE_FALSE(rect.contains(point));
  point.x = 11;
  point.y = 11;
  REQUIRE_FALSE(rect.contains(point));
}

TEST_CASE("Rect can detect if a rect is contained within", "[Rect]") {
  Adagio::Rect<int> rect1(0, 0, 10, 10);
  Adagio::Rect<int> rect2(1, 1, 1, 1);
  REQUIRE(rect1.contains(rect2));
  rect2.position = {-5, -5};
  REQUIRE_FALSE(rect1.contains(rect2));
  rect2.position = {15, 15};
  REQUIRE_FALSE(rect1.contains(rect2));
  rect2.position = {9, 9};
  REQUIRE(rect1.contains(rect2));
}

TEST_CASE("Rect can detect if a rect intersects it at all", "[Rect]") {
  Adagio::Rect<int> rect1(0, 0, 10, 10);
  Adagio::Rect<int> rect2(1, 1, 2, 2);
  REQUIRE(rect1.intersects(rect2));
  rect2.position = {-1, -1};
  REQUIRE(rect1.intersects(rect2));
  rect2.position = {-10, -10};
  REQUIRE_FALSE(rect1.intersects(rect2));
  rect2.position = {5, -10};
  REQUIRE_FALSE(rect1.intersects(rect2));
  rect2.position = {9, 9};
  REQUIRE(rect1.intersects(rect2));
  rect2.position = {11, 11};
  REQUIRE_FALSE(rect1.intersects(rect2));
  rect2.position = {5, 11};
  REQUIRE_FALSE(rect1.intersects(rect2));
}

TEST_CASE("Rect can cast to string", "[Rect]") {
  Adagio::Rect<int> rect(1, 2, 3, 4);
  REQUIRE(rect.to_string() == "Rect(1,2,3,4)");
}

TEST_CASE("Rect can handle weird sizes", "[Rect]") {
  Adagio::Rect<float> rect(0, 0, -5, -5);
  REQUIRE(rect.x() == -5);
  REQUIRE(rect.y() == -5);
  REQUIRE(rect.width() == 5);
  REQUIRE(rect.height() == 5);
}

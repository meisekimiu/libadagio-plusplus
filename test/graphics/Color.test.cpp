#include <catch2/catch.hpp>
#include "../../src/graphics/Color.h"

TEST_CASE("Color exists", "[Color]") {
    Adagio::Color c;
}

TEST_CASE("Color initializers", "[Color]") {
    Adagio::Color c{255, 255, 255, 255};

    SECTION("Color sets alpha to 255 by default") {
        Adagio::Color rgb{255, 255, 255};
        REQUIRE(rgb.a == 255);
    }
}

TEST_CASE("Color initialized from hex code", "[Color]") {
    SECTION("Color from hex triple") {
        auto color = Adagio::Color::fromHexCode("#fff");
        REQUIRE(color.r == 255);
        REQUIRE(color.g == 255);
        REQUIRE(color.b == 255);
        REQUIRE(color.a == 255);
    }

    SECTION("Color from six digit hex code") {
        auto color = Adagio::Color::fromHexCode("#123456");
        REQUIRE(color.r == 0x12);
        REQUIRE(color.g == 0x34);
        REQUIRE(color.b == 0x56);
        REQUIRE(color.a == 255);
    }

    SECTION("Color from 4 digit code") {
        auto color = Adagio::Color::fromHexCode("#1234");
        REQUIRE(color.r == 0x11);
        REQUIRE(color.g == 0x22);
        REQUIRE(color.b == 0x33);
        REQUIRE(color.a == 0x44);
    }

    SECTION("Color from 8 digit code") {
        auto color = Adagio::Color::fromHexCode("#abcdef12");
        REQUIRE(color.r == 0xab);
        REQUIRE(color.g == 0xcd);
        REQUIRE(color.b == 0xef);
        REQUIRE(color.a == 0x12);
    }

    SECTION("Exception thrown from an invalid code") {
        REQUIRE_THROWS(Adagio::Color::fromHexCode("#12"));
        REQUIRE_THROWS(Adagio::Color::fromHexCode("#12324234124"));
        REQUIRE_THROWS(Adagio::Color::fromHexCode("potato"));
        REQUIRE_THROWS(Adagio::Color::fromHexCode("00tato"));
        REQUIRE_THROWS(Adagio::Color::fromHexCode("0000to"));
        REQUIRE_THROWS(Adagio::Color::fromHexCode("000000zz"));
    }
}

TEST_CASE("Color can be converted to hex", "[Color]") {
    Adagio::Color c{0x12, 0x34, 0x56};
    REQUIRE(c.toHex() == "#123456");

    SECTION("Include alpha if not opaque") {
        c = {0xff, 0xff, 0xff, 0x66};
        REQUIRE(c.toHex() == "#ffffff66");
    }
}

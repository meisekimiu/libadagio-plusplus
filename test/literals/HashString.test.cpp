#include "../../src/literals/HashString.h"
#include <catch2/catch.hpp>

TEST_CASE("HashString literal", "[literals]") {
    // TESTING TIP:
    // Use a breakpoint to verify that these are generated at compile time
    unsigned int hash = "potato"_hs;
    auto hash2 = "POTATO"_hs;
    auto hash3 = "potatp"_hs;
    auto hash4 = "abcdefghijklmnopqrstuvwxyz"_hs;
    REQUIRE(hash != 0);
    REQUIRE(hash != hash2);
    REQUIRE(hash2 != hash3);
    REQUIRE(hash3 != hash4);
}

TEST_CASE("crc32", "[literals]") {
    const unsigned int hash = Adagio::crc("test", 4);
    const unsigned int hash2 = Adagio::crc("tets", 4);
    REQUIRE(hash != 0);
    REQUIRE(hash != hash2);
}

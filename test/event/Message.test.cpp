#include "../../src/event/Message.h"
#include <catch2/catch.hpp>

TEST_CASE("Message object", "[event]") {
    SECTION("Takes in event arguments", "[event]") {
        Adagio::Message event;
        event.addIntArg("test"_hs, 1337).addBoolArg(
                "test2"_hs, false);
        auto value = event.getArg(0);
        auto value2 = event.getArg(1);
        REQUIRE(value->eventName == "test"_hs);
        REQUIRE(value->type == Adagio::TYPE_INT);
        REQUIRE(value->m_Int == 1337);
        REQUIRE(value2->eventName == "test2"_hs);
        REQUIRE(value2->type == Adagio::TYPE_BOOL);
        REQUIRE(value2->m_Bool == false);
    }SECTION("Throws an error if you add too many arguments", "[event]") {
        Adagio::Message event;
        event.addFloatArg("test"_hs, 3.14159f).addUintArg("test2"_hs, 1337).addBoolArg("test3"_hs, true).addIntArg(
                "test4"_hs, -1337);
        REQUIRE_THROWS(event.addIntArg("exception"_hs, 666));
    } SECTION("Can look up an argument by hash name", "[event]") {
        Adagio::Message event;
        event.addIntArg("abcd"_hs, 1337).addBoolArg("efgh"_hs, true);
        REQUIRE(event.getArgByName("abcd"_hs)->m_Int == 1337);
        REQUIRE(event.getArgByName("efgh"_hs)->m_Bool);
        REQUIRE(event.getArgByName("nonexist"_hs) == nullptr);
    } SECTION("Can clear event arguments", "[event]") {
        Adagio::Message event;
        event.addIntArg("abcd"_hs, 1337).addBoolArg("efgh"_hs, true);
        REQUIRE(event.getArgumentCount() == 2);
        event.nullifyArguments();
        REQUIRE(event.getArgumentCount() == 0);
        REQUIRE(event.getArg(0)->eventName == 0);
    } SECTION("Has from, to, and active properties", "[event]") {
        Adagio::Message event;
        event.from = 1337;
        event.to = 666;
        event.active = true;
    }
}

#include "../../src/event/MessageCollection.h"
#include <catch2/catch.hpp>

TEST_CASE("MessageCollection", "[event]") {
    Adagio::MessageCollection collection;

    SECTION("Can calculate count", "[event]") {
        REQUIRE(collection.empty());
    }

    SECTION("Can add a single event", "[event]") {
        Adagio::Message event;
        event.name = "test"_hs;
        collection.append(&event);
        REQUIRE(collection.first == &event);
        REQUIRE(collection.size() == 1);
    }

    SECTION("Can add two events", "[event]") {
        Adagio::Message eventA, eventB;
        collection.append(&eventA);
        collection.append(&eventB);
        REQUIRE(collection[0] == &eventA);
        REQUIRE(collection[1] == &eventB);
        REQUIRE(collection.size() == 2);
    }

    SECTION("Can add many events", "[event]") {
        Adagio::Message events[10];
        for (int i = 0; i < 10; i++) {
            collection.append(&events[i]);
            REQUIRE(collection[i] == &events[i]);
        }
        REQUIRE(collection.size() == 10);
    }

    SECTION("Can remove an event in the middle of the collection", "[event]") {
        Adagio::Message events[10];
        for (auto &event: events) {
            collection.append(&event);
        }
        collection.remove(3);
        REQUIRE(collection.size() == 9);
        REQUIRE(collection[2]->links.next == &events[4]);
        REQUIRE(events[4].links.prev == collection[2]);
    }

    SECTION("Can remove the only event", "[event]") {
        Adagio::Message event;
        collection.append(&event);
        collection.remove(0);
        REQUIRE(collection.empty());
        REQUIRE(collection.first == nullptr);
        REQUIRE(collection.last == nullptr);
    }

    SECTION("Can pop off the first element", "[event]") {
        Adagio::Message events[10];
        for (auto &event: events) {
            collection.append(&event);
        }
        Adagio::Message *first = collection.first;
        while (Adagio::Message *e = collection.shift()) {
            REQUIRE(first == e);
            first = collection.first;
        }
        REQUIRE(collection.empty());
    }
}

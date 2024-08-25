#include "../../src/event/MessageDispatchService.h"
#include <catch2/catch.hpp>

struct TestInbox {
    Adagio::MessageCollection messages;
};


TEST_CASE("MessageDispatchService can send an event to an inbox", "[event]") {
    Adagio::MessageDispatchService events;
    TestInbox inbox;
    events.registerInbox(1, inbox);
    auto event = events.dispatch(1, 0, "test"_hs).addBoolArg("isTesting"_hs, true);
    REQUIRE(event.active);
    REQUIRE(event.from == 0);
    REQUIRE(event.to == 1);
    REQUIRE(event.name == "test"_hs);
    REQUIRE(inbox.messages.size() == 1);
    REQUIRE(inbox.messages[0]->getArg(0)->m_Bool);
}

TEST_CASE("MessageDispatchService can send multiple events to an inbox", "[event]") {
    Adagio::MessageDispatchService events;
    TestInbox inbox;
    events.registerInbox(1, inbox);
    events.dispatch(1, 0, "test"_hs);
    events.dispatch(1, 0, "test2"_hs);
    REQUIRE(inbox.messages.size() == 2);
    REQUIRE(inbox.messages[0]->name == "test"_hs);
    REQUIRE(inbox.messages[1]->name == "test2"_hs);
}

TEST_CASE("MessageDispatchService properly pools message objects", "[event]") {
    Adagio::MessageDispatchService events;
    TestInbox inbox;
    events.registerInbox(1, inbox);
    Adagio::Message *const event = &events.dispatch(1, 0, "test"_hs);
    inbox.messages.remove(0);
    Adagio::Message *const newEvent = &events.dispatch(1, 0, "newEvent"_hs);
    REQUIRE(event == newEvent);
}

TEST_CASE("MessageDispatchService does not give up a pooled message if no one receives it", "[event]") {
    Adagio::MessageDispatchService events;
    TestInbox inbox;
    events.registerInbox(1, inbox);
    Adagio::Message *const unsentMessage = &events.dispatch(1337, 0, "invalid"_hs);
    Adagio::Message *const sentMessage = &events.dispatch(1, 0, "test"_hs);
    REQUIRE(sentMessage != unsentMessage);
    REQUIRE(unsentMessage->name != "invalid"_hs);
}

TEST_CASE("MessageDispatchService can unregister an inbox", "[event]") {
    Adagio::MessageDispatchService events;
    TestInbox inbox;
    events.registerInbox(1, inbox);
    events.unregisterInbox(1);
    events.dispatch(1, 0, "test"_hs).addBoolArg("isTest"_hs, true);
    REQUIRE(inbox.messages.empty());
}

TEST_CASE("MessageDispatchService will fail silently if message pool is full", "[event]") {
    Adagio::MessageDispatchService events;
    TestInbox inbox;
    events.registerInbox(1, inbox);
    for (int i = 0; i < MSGPOOL_MAX; i++) {
        events.dispatch(1, 0, "test"_hs);
    }
    REQUIRE(inbox.messages.size() == MSGPOOL_MAX);

    Adagio::Message &message = events.dispatch(1, 0, "test"_hs);
    REQUIRE(message.name == 0xdeadbeef);
    REQUIRE_FALSE(message.active);
    REQUIRE(inbox.messages.size() == MSGPOOL_MAX);
}

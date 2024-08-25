#include "../game/EcsTestingHarness.h"
#include "../../../src/game/components/events/MessageInbox.h"
#include "../../../src/event/MessageDispatchService.h"
#include "../../../src/game/components/events/hooks/MessageInboxHooks.h"
#include <catch2/catch.hpp>

TEST_CASE("MessageInbox ECS Hooks", "[event]") {
    Adagio::MessageDispatchService messageService;
    EcsTestingHarness harness;
    auto &registry = harness.registry;
    registry.ctx().emplace<Adagio::MessageDispatchService *>(&messageService);
    registry.on_construct<MessageInbox>().connect<&RegisterInboxWithMessageService>();
    registry.on_destroy<MessageInbox>().connect<&UnregisterInboxWithMessageService>();

    SECTION("A component is registered with the message service", "[event]") {
        auto entity = registry.create();
        auto &inbox = registry.emplace<MessageInbox>(entity);
        messageService.dispatch(entity, 0, "test"_hs);
        REQUIRE(inbox.messages.size() == 1);
        REQUIRE(inbox.messages.first->name == "test"_hs);
    }

    SECTION("A component can be deregistered with the message service", "[event]") {
        auto entity = registry.create();
        auto &inbox = registry.emplace<MessageInbox>(entity);
        registry.destroy(entity);
        messageService.dispatch(entity, 0, "test"_hs);
        REQUIRE(inbox.messages.empty());
    }
}

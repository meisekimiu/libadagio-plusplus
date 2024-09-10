#include "../../EcsTestingHarness.h"
#include "../../../../src/game/components/Dead.h"
#include "../../../../src/game/systems/WallopEvents.h"
#include "../../../../src/game/factories/MakeWallop.h"
#include "../../../../src/game/components/events/MessageInbox.h"
#include "../../../../src/game/components/events/hooks/MessageInboxHooks.h"
#include <catch2/catch.hpp>

TEST_CASE("Wallop Events", "[gracilis][system]") {
    EcsTestingHarness harness;
    harness.registry.on_construct<MessageInbox>().connect<&RegisterInboxWithMessageService>();
    harness.registry.on_destroy<MessageInbox>().connect<&UnregisterInboxWithMessageService>();
    const auto wallop = MakeWallop({64, 64}, -M_PI_2, harness.registry, harness.gameServices.resources.textureManager);

    const auto enemy = harness.registry.create();
    const auto &enemyInbox = harness.registry.emplace<MessageInbox>(enemy);

    SECTION("Does nothing with no events") {
        harness.testSystemFrame(WallopEventsSystem);

        REQUIRE_FALSE(harness.registry.any_of<Dead>(wallop));
    }

    SECTION("Does nothing with no collision events") {
        harness.messageService.dispatch(wallop, 0, "potato"_hs);
        harness.testSystemFrame(WallopEventsSystem);

        REQUIRE_FALSE(harness.registry.any_of<Dead>(wallop));
    }

    SECTION("Collision event kills the wallop") {
        harness.messageService.dispatch(wallop, enemy, "COLLISION"_hs);
        harness.testSystemFrame(WallopEventsSystem);

        REQUIRE(harness.registry.any_of<Dead>(wallop));
        REQUIRE_FALSE(enemyInbox.messages.empty());
        REQUIRE(enemyInbox.messages[0]->name == "hit"_hs);
    }
}

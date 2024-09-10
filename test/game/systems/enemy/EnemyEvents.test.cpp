#include "../../EcsTestingHarness.h"
#include "../../../../src/game/components/Dead.h"
#include "../../../../src/game/components/events/MessageInbox.h"
#include "../../../../src/game/components/events/hooks/MessageInboxHooks.h"
#include "../../../../src/game/components/Enemy.h"
#include "../../../../src/game/systems/EnemyEvents.h"
#include <catch2/catch.hpp>

TEST_CASE("Enemy events", "[gracilis]") {
    EcsTestingHarness harness;
    entt::registry &registry = harness.registry;
    registry.on_construct<MessageInbox>().connect<&RegisterInboxWithMessageService>();
    registry.on_destroy<MessageInbox>().connect<&UnregisterInboxWithMessageService>();

    const auto enemy = registry.create();
    auto &enemyComponent = registry.emplace<Enemy>(enemy);
    auto &inbox = registry.emplace<MessageInbox>(enemy);

    SECTION("Takes damage on 'hit' event") {
        enemyComponent.hp = 10;
        harness.gameServices.messageDispatchService->dispatch(enemy, 1337, "hit"_hs);

        harness.testSystemFrame(EnemyEventsSystem);

        REQUIRE(!registry.any_of<Dead>(enemy));
        REQUIRE(enemyComponent.hp == 9);
        REQUIRE(inbox.messages.empty());
    }

    SECTION("Dies when HP is 0") {
        enemyComponent.hp = 1;
        harness.gameServices.messageDispatchService->dispatch(enemy, 1337, "hit"_hs);
        harness.gameServices.messageDispatchService->dispatch(enemy, 1337, "hit"_hs);
        harness.gameServices.messageDispatchService->dispatch(enemy, 1337, "hit"_hs);

        harness.testSystemFrame(EnemyEventsSystem);

        REQUIRE(registry.any_of<Dead>(enemy));
        REQUIRE(enemyComponent.hp == 0);
    }
}

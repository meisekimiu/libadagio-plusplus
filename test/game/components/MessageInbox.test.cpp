#include "../../../src/game/components/events/MessageInbox.h"
#include "../EcsTestingHarness.h"
#include <catch2/catch.hpp>

TEST_CASE("MessageInbox has pointer stability", "[component]") {
    EcsTestingHarness harness;
    entt::registry &registry = harness.registry;
    constexpr unsigned int entityCount = 10;
    entt::entity entities[entityCount];
    for (auto &entity: entities) {
        entity = registry.create();
        registry.emplace<MessageInbox>(entity);
    }
    const Adagio::MessageCollection *const address = &registry.get<MessageInbox>(entities[entityCount - 1]).messages;
    for (int i = 0; i < entityCount - 1; i++) {
        registry.destroy(entities[i]);
    }
    const Adagio::MessageCollection *const addressAfterDelete = &registry.get<MessageInbox>(
            entities[entityCount - 1]).messages;
    REQUIRE(address == addressAfterDelete);
}

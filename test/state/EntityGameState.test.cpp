#include "../../src/state/EntityGameState.h"
#include "../../src/state/StateMachine.h"
#include "../graphics/MockGraphicsDevice.h"
#include "mocks/MockStats.h"
#include <catch2/catch.hpp>

struct TestComponent {
  int updateCount;
  int drawCount;
};

class TestEntityState : public Adagio::EntityGameState {
public:
  void configureRegistry(void (*fn)(entt::registry &)) { fn(registry); }

  [[nodiscard]] unsigned long getRegistrySize() const {
    return registry.storage<entt::entity>()->in_use();
  }

  [[nodiscard]] unsigned long getSystemCount() const {
    return getSystems()->size();
  }

  [[nodiscard]] unsigned long getRendererCount() const {
    return getRenderers()->size();
  }

  [[nodiscard]] std::vector<TestComponent> getTestComponents() const {
    std::vector<TestComponent> vec;
    vec.reserve(registry.storage<entt::entity>()->in_use());
    auto view = registry.view<TestComponent>();
    for (auto [entity, test] : view.each()) {
      vec.push_back(test);
    }
    return vec;
  }
};

void testSystem(entt::registry &registry, Adagio::GameStats &stats,
                Adagio::StateMachine *stateMachine) {
  auto view = registry.view<TestComponent>();
  for (auto [entity, test] : view.each()) {
    test.updateCount++;
  }
}

void testRenderer(entt::registry &registry, Adagio::SpriteBatch &sb,
                  Adagio::RenderingServices &services) {
  auto view = registry.view<TestComponent>();
  for (auto [entity, test] : view.each()) {
    test.drawCount++;
  }
}

static MockGraphicsDevice gd;
static Adagio::SpriteBatch spriteBatch(&gd);
static Adagio::RenderingServices nullServices{nullptr, nullptr, nullptr};
static Adagio::StateMachine stateMachine(&spriteBatch, &nullServices);

TEST_CASE("EntityGameState exists", "[EntityGameState]") {
  Adagio::EntityGameState state;
}

TEST_CASE("TestEntityState scaffolding", "[EntityGameState]") {
  TestEntityState state;

  SECTION("It can run code on the registry") {
    REQUIRE(state.getRegistrySize() == 0);
    state.configureRegistry([](entt::registry &registry) {
      auto entity = registry.create();
      registry.emplace<TestComponent>(entity, 0);
    });
    REQUIRE(state.getRegistrySize() == 1);
  }

  SECTION("It can add systems") {
    REQUIRE(state.getSystemCount() == 0);
    state.registerSystem(testSystem);
    REQUIRE(state.getSystemCount() == 1);
  }

  SECTION("It can add renderers") {
    REQUIRE(state.getRendererCount() == 0);
    state.registerRenderer(testRenderer);
    REQUIRE(state.getRendererCount() == 1);
  }
}

TEST_CASE("EntityGameState runs systems", "[EntityGameState]") {
  TestEntityState state;
  MockStats stats;
  Adagio::RenderingServices renderingServices{&spriteBatch, nullptr, &stats};
  REQUIRE(state.getTestComponents().empty());
  state.configureRegistry([](entt::registry &registry) {
    auto entity = registry.create();
    registry.emplace<TestComponent>(entity, 0);
  });
  REQUIRE(state.getTestComponents().size() == 1);

  SECTION("It can run with no systems") {
    REQUIRE_NOTHROW(state.update(stats, &stateMachine));
    REQUIRE(state.getTestComponents()[0].updateCount == 0);
  }

  SECTION("It can run with no renderers") {
    REQUIRE_NOTHROW(state.draw(spriteBatch, renderingServices));
    REQUIRE(state.getTestComponents()[0].drawCount == 0);
  }

  SECTION("It runs one system") {
    state.registerSystem(testSystem);
    state.update(stats, &stateMachine);
    auto testComponents = state.getTestComponents();
    REQUIRE_FALSE(testComponents.empty());
    REQUIRE(testComponents[0].updateCount == 1);
  }

  SECTION("It runs one renderer") {
    state.registerRenderer(testRenderer);
    state.draw(spriteBatch, renderingServices);
    auto testComponents = state.getTestComponents();
    REQUIRE_FALSE(testComponents.empty());
    REQUIRE(testComponents[0].drawCount == 1);
  }
}

TEST_CASE("EntityGameState edge cases", "[EntityGameState]") {
  TestEntityState state;
  MockStats stats;

  SECTION("Null state machine") {
    REQUIRE_THROWS(state.update(stats, nullptr));
  }

  SECTION("Adding a null system") {
    REQUIRE_THROWS(state.registerSystem(nullptr));
  }

  SECTION("Adding a null renderer") {
    REQUIRE_THROWS(state.registerRenderer(nullptr));
  }
}

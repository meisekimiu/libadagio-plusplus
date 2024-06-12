#include "../../src/state/Runner.h"
#include "../graphics/MockGraphicsDevice.h"
#include "mocks/TestGame.h"
#include <catch2/catch.hpp>

class TestingRunner : public Adagio::Runner {
public:
  explicit TestingRunner(Adagio::Game *g, Adagio::GameState *initialState)
      : Adagio::Runner(g, initialState) {}

  void closeGameNextLoop() { closeGame = true; }

protected:
  bool closeGame{false};

  bool shouldCloseGame() override { return closeGame; }
};

class RunnerTestingState : public Adagio::GameState {
public:
  void update(Adagio::GameStats &stats,
              Adagio::StateMachine *gameStates) override {
    updateCalls++;
    if (--loops <= 0) {
      stats.closeGame();
    }
  }

  void reset() {
    loops = 1;
    updateCalls = 0;
  }

  short updateCalls{0};
  short loops{1};
};

static MockGraphicsDevice graphicsDevice;
static Adagio::SpriteBatch spriteBatch(&graphicsDevice);

TEST_CASE("Runner exists", "[Runner]") {
  TestGame game{spriteBatch};
  RunnerTestingState state;
  Adagio::Runner runner(&game, &state);
}

TEST_CASE("Runner throws when passed null values", "[Runner]") {
  TestGame game{spriteBatch};
  RunnerTestingState state;

  SECTION("Null game", "[Runner]") {
    REQUIRE_THROWS(Adagio::Runner(nullptr, &state));
  }

  SECTION("Null state", "[Runner]") {
    REQUIRE_THROWS(Adagio::Runner(&game, nullptr));
  }

  SECTION("Both null", "[Runner]") {
    REQUIRE_THROWS(Adagio::Runner(nullptr, nullptr));
  }
}

TEST_CASE("Runner runs through game", "[Runner]") {
  TestGame game{spriteBatch};
  RunnerTestingState state;
  TestingRunner runner(&game, &state);

  SECTION("One loop", "[Runner]") {
    runner.run();
    REQUIRE(game.calledInit);
    REQUIRE(game.calledLoadContent);
    REQUIRE(state.updateCalls == 1);
    REQUIRE(game.calledUnloadContent);
    REQUIRE(game.calledCleanup);
  }

  SECTION("Ten loops", "[Runner]") {
    state.reset();
    state.loops = 10;
    runner.run();
    REQUIRE(state.updateCalls == 10);
  }

  SECTION("Simulated window interrupt", "[Runner]") {
    state.reset();
    runner.closeGameNextLoop();
    runner.run();
    REQUIRE(state.updateCalls == 0);
  }
}

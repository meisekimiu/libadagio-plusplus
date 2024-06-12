#include "../../src/state/Game.h"
#include "../graphics/MockGraphicsDevice.h"
#include "mocks/EmptyGameState.h"
#include "mocks/TestGame.h"
#include <catch2/catch.hpp>

static MockGraphicsDevice graphicsDevice;
static Adagio::SpriteBatch spriteBatch(&graphicsDevice);

TEST_CASE("Game class exists", "[Game]") { TestGame game{spriteBatch}; }

TEST_CASE("Game class can hold states", "[Game]") {
  TestGame game{spriteBatch};
  EmptyGameState state = EmptyGameState();
  game.stateMachine.pushState(&state);

  SECTION("It can update its Game States", "[Game]") {
    game.update();
    REQUIRE(state.calledUpdate());
  }

  SECTION("It can draw its Game States", "[Game]") {
    game.draw();
    REQUIRE(state.calledDraw());
  }
}

TEST_CASE("Game can check running state", "[Game]") {
  TestGame game{spriteBatch};
  REQUIRE(game.isRunning());

  SECTION("It can stop game", "[Game]") {
    game.closeGame();
    REQUIRE_FALSE(game.isRunning());
  }
}

TEST_CASE("Game has lifecycle methods", "[Game]") {
  TestGame game{spriteBatch};
  game.init();
  REQUIRE(game.calledInit);

  SECTION("LoadContent", "[Game]") {
    REQUIRE_FALSE(game.calledLoadContent);
    game.loadContent();
    REQUIRE(game.calledLoadContent);
  }

  SECTION("UnloadContent", "[Game]") {
    REQUIRE_FALSE(game.calledUnloadContent);
    game.unloadContent();
    REQUIRE(game.calledUnloadContent);
  }

  SECTION("Cleanup", "[Game]") {
    REQUIRE_FALSE(game.calledCleanup);
    game.cleanup();
    REQUIRE(game.calledCleanup);
  }
}

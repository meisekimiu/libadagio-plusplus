#include <catch2/catch.hpp>
#include "../../src/graphics/SpriteBatch.h"
#include "../graphics/MockGraphicsDevice.h"
#include "../../src/state/StateMachine.h"
#include "mocks/EmptyGameState.h"
#include "mocks/MockStats.h"

static MockGraphicsDevice graphicsDevice;
static Adagio::SpriteBatch spriteBatch(&graphicsDevice);


TEST_CASE("StateMachine exists", "[StateMachine]") {
    Adagio::StateMachine stateMachine(&spriteBatch);
}

TEST_CASE("An empty StateMachine", "[StateMachine]") {
    Adagio::StateMachine stateMachine(&spriteBatch);
    MockStats stats;
    SECTION("Can update") {
        stateMachine.update(&stats);
    }

    SECTION("Can draw") {
        stateMachine.draw(&stats);
    }

    SECTION("Can pop state without error") {
        stateMachine.popState();
    }
}

TEST_CASE("A StateMachine with one state", "[StateMachine]") {
    Adagio::StateMachine stateMachine(&spriteBatch);
    MockStats stats;
    EmptyGameState state;
    stateMachine.pushState(&state);

    SECTION("Calls Init() on state") {
        REQUIRE(state.calledInit());
    }

    SECTION("Calls LoadContent() on state") {
        REQUIRE(state.calledLoadContent());
    }

    SECTION("Calls update() on state") {
        stateMachine.update(&stats);
        REQUIRE(state.calledUpdate());
        REQUIRE(state.lastFrameTime() == 1.0);
        REQUIRE(state.lastGameTime() == 0.0);
    }

    SECTION("Calls draw() on state") {
        stateMachine.draw(&stats);
        REQUIRE(state.calledDraw());
    }

    SECTION("Calls pause() on state when pushing a new state") {
        EmptyGameState state2;
        stateMachine.pushState(&state2);
        REQUIRE(state.calledPause());

        SECTION("Calls resume() on state when popping the new state") {
            stateMachine.popState();
            REQUIRE(state.calledResume());
        }
    }

    SECTION("Can pop the last state") {
        stateMachine.popState();

        SECTION("It unloads the last state") {
            REQUIRE(state.calledUnloadContent());
        }

        SECTION("It runs cleanup() on last state") {
            REQUIRE(state.calledCleanup());
        }
    }
}

TEST_CASE("A StateMachine with two states", "[StateMachine]") {
    Adagio::StateMachine stateMachine(&spriteBatch);
    MockStats stats;
    EmptyGameState state;
    EmptyGameState state2;
    stateMachine.pushState(&state);
    stateMachine.pushState(&state2);

    SECTION("Calls update() only on top state") {
        stateMachine.update(&stats);
        REQUIRE(state2.calledUpdate());
        REQUIRE_FALSE(state.calledUpdate());
    }

    SECTION("Calls draw() only on top state (if opaque)") {
        stateMachine.draw(&stats);
        REQUIRE(state2.calledDraw());
        REQUIRE_FALSE(state.calledDraw());
    }

    SECTION("Calls draw() on next state if top state is transparent") {
        state.reset();
        state2.reset();
        state2.transparent = true;
        stateMachine.draw(&stats);
        REQUIRE(state2.calledDraw());
        REQUIRE(state.calledDraw());
    }
}

TEST_CASE("Degenerate StateMachine cases", "[StateMachine]") {
    SECTION("Null SpriteBatch") {
        REQUIRE_THROWS(Adagio::StateMachine(nullptr));
    }

    SECTION("Null GameState") {
        Adagio::StateMachine stateMachine(&spriteBatch);
        REQUIRE_THROWS(stateMachine.pushState(nullptr));
    }

    SECTION("Null GameStats") {
        Adagio::StateMachine stateMachine(&spriteBatch);
        EmptyGameState state;
        stateMachine.pushState(&state);

        SECTION("Update") {
            REQUIRE_THROWS(stateMachine.update(nullptr));
        }

        SECTION("Draw") {
            REQUIRE_THROWS(stateMachine.draw(nullptr));
        }
    }
}

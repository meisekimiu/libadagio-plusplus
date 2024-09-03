#include "../../src/state/StateMachine.h"
#include "../../src/graphics/SpriteBatch.h"
#include "../graphics/MockGraphicsDevice.h"
#include "mocks/EmptyGameState.h"
#include "mocks/MockStats.h"
#include <catch2/catch.hpp>

static MockGraphicsDevice graphicsDevice;
static Adagio::SpriteBatch spriteBatch(&graphicsDevice);
static Adagio::RenderingServices nullServices{nullptr, nullptr, nullptr};
static MockStats stats;
static Adagio::GameServices gameServices{nullptr, &stats};

TEST_CASE("StateMachine exists", "[StateMachine]") {
    Adagio::StateMachine stateMachine(&spriteBatch, &nullServices);
}

TEST_CASE("An empty StateMachine", "[StateMachine]") {
    Adagio::RenderingServices renderingServices{&spriteBatch, nullptr, &stats};
    Adagio::StateMachine stateMachine(&spriteBatch, &renderingServices);
    SECTION("Can update") { stateMachine.update(gameServices); }

    SECTION("Can draw") { stateMachine.draw(); }

    SECTION("Can pop state without error") { stateMachine.popState(); }
}

TEST_CASE("A StateMachine with one state", "[StateMachine]") {
    EmptyGameState state;
    Adagio::RenderingServices renderingServices{&spriteBatch, nullptr, &stats};
    Adagio::StateMachine stateMachine(&spriteBatch, &renderingServices);
    stateMachine.pushState(&state);

    SECTION("Calls Init() on state") { REQUIRE(state.calledInit()); }

    SECTION("Calls LoadContent() on state") {
        REQUIRE(state.calledLoadContent());
    }

    SECTION("Calls update() on state") {
        stateMachine.update(gameServices);
        REQUIRE(state.calledUpdate());
        REQUIRE(state.lastFrameTime() == 1.0);
        REQUIRE(state.lastGameTime() == 0.0);
    }

    SECTION("Calls draw() on state") {
        stateMachine.draw();
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
    MockStats stats;
    Adagio::RenderingServices renderingServices{&spriteBatch, nullptr, &stats};
    Adagio::StateMachine stateMachine(&spriteBatch, &renderingServices);
    EmptyGameState state;
    EmptyGameState state2;
    stateMachine.pushState(&state);
    stateMachine.pushState(&state2);

    SECTION("Calls update() only on top state") {
        stateMachine.update(gameServices);
        REQUIRE(state2.calledUpdate());
        REQUIRE_FALSE(state.calledUpdate());
    }

    SECTION("Calls draw() only on top state (if opaque)") {
        stateMachine.draw();
        REQUIRE(state2.calledDraw());
        REQUIRE_FALSE(state.calledDraw());
    }

    SECTION("Calls draw() on next state if top state is transparent") {
        state.reset();
        state2.reset();
        state2.transparent = true;
        stateMachine.draw();
        REQUIRE(state2.calledDraw());
        REQUIRE(state.calledDraw());
    }

    SECTION("It unloads the state on destruction") {
        auto *sm = new Adagio::StateMachine(&spriteBatch, &renderingServices);
        state.reset();
        state2.reset();
        sm->pushState(&state);
        sm->pushState(&state2);
        delete sm;
        REQUIRE(state.calledUnloadContent());
        REQUIRE(state2.calledUnloadContent());
        REQUIRE(state.calledCleanup());
        REQUIRE(state2.calledCleanup());
        REQUIRE_FALSE(state.calledResume());
        REQUIRE_FALSE(state2.calledResume());
    }
}

TEST_CASE("Degenerate StateMachine cases", "[StateMachine]") {
    Adagio::RenderingServices nullServices{nullptr, nullptr, nullptr};
    SECTION("Null SpriteBatch") {
        REQUIRE_THROWS(Adagio::StateMachine(nullptr, &nullServices));
    }

    SECTION("Null GameState") {
        Adagio::StateMachine stateMachine(&spriteBatch, &nullServices);
        REQUIRE_THROWS(stateMachine.pushState(nullptr));
    }

    SECTION("Null GameStats") {
        Adagio::StateMachine stateMachine(&spriteBatch, &nullServices);
        EmptyGameState state;
        stateMachine.pushState(&state);
        Adagio::GameServices trulyNullGameServices;

        SECTION("Update") { REQUIRE_THROWS(stateMachine.update(trulyNullGameServices)); }
    }
}

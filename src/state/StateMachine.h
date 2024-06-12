#ifndef GL_ADAGIO_STATEMACHINE_H
#define GL_ADAGIO_STATEMACHINE_H

#include "../graphics/SpriteBatch.h"
#include "./GameState.h"
#include "./GameStats.h"
#include "RenderingServices.h"
#include <vector>

namespace Adagio {

class StateMachine {
public:
  explicit StateMachine(SpriteBatch *spriteBatch, RenderingServices *services);

  ~StateMachine();

  void update(GameStats *stats);

  void draw();

  void pushState(GameState *state);

  void popState();

  void changeState(GameState *state);

private:
  std::vector<GameState *> states;

  void addStateToVector(GameState *state);

  void popFinalState();

  SpriteBatch *spriteBatch;

  void checkGameStats(const GameStats *stats);

  RenderingServices *services;
};
} // namespace Adagio

#endif // GL_ADAGIO_STATEMACHINE_H

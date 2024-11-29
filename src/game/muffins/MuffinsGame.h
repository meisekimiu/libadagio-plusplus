#ifndef GL_ADAGIO_MUFFINSGAME_H
#define GL_ADAGIO_MUFFINSGAME_H

#include "../../state/Game.h"
#include "../../state/StateMachine.h"

namespace Muffins {

class MuffinsGame : public Adagio::Game {
public:
  explicit MuffinsGame(Adagio::SpriteBatch &sb);

  void init() override;
};

} // namespace Muffins

#endif // GL_ADAGIO_MUFFINSGAME_H

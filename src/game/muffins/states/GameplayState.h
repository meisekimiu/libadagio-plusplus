#ifndef GL_ADAGIO_GAMEPLAYSTATE_H
#define GL_ADAGIO_GAMEPLAYSTATE_H

#include "../../../state/EntityGameState.h"
namespace Muffins {

class GameplayState : public Adagio::EntityGameState {
public:
  void init() override;
  void loadContent(Adagio::SpriteBatch &spriteBatch, Adagio::RenderingServices &services) override;
};

} // namespace Muffins

#endif // GL_ADAGIO_GAMEPLAYSTATE_H

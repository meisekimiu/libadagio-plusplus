#ifndef GL_ADAGIO_MOCKGAMESTATS_H
#define GL_ADAGIO_MOCKGAMESTATS_H

#include "../../../src/state/GameStats.h"

class MockGameStats : public Adagio::GameStats {
public:
    [[nodiscard]] bool isRunning() const override;

    void closeGame() override;

    [[nodiscard]] float getFrameDelta() const override;

    [[nodiscard]] double getGameTime() const override;

    void advanceTime(double delta);

    void reset();

protected:
    bool running{true};
    double gameTime{0.0};
    double lastTickTime{0.0};
};


#endif //GL_ADAGIO_MOCKGAMESTATS_H

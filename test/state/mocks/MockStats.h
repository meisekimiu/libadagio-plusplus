#ifndef GL_ADAGIO_MOCKSTATS_H
#define GL_ADAGIO_MOCKSTATS_H

#include "../../../src/state/GameStats.h"

class MockStats : public Adagio::GameStats {
public:
    [[nodiscard]] double getGameTime() const override;

    [[nodiscard]] float getFrameDelta() const override;

    [[nodiscard]] bool isRunning() const override;

    void closeGame() override;
};

#endif //GL_ADAGIO_MOCKSTATS_H

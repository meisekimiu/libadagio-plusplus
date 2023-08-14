#ifndef GL_ADAGIO_GAMESTATS_H
#define GL_ADAGIO_GAMESTATS_H

namespace Adagio {
    class GameStats {
    public:
        virtual bool isRunning() const = 0;

        virtual double getGameTime() const = 0;

        virtual float getFrameDelta() const = 0;

        virtual void closeGame() = 0;
    };
}

#endif //GL_ADAGIO_GAMESTATS_H

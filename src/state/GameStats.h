#ifndef GL_ADAGIO_GAMESTATS_H
#define GL_ADAGIO_GAMESTATS_H

namespace Adagio {
    class GameStats {
    public:
        [[nodiscard]] virtual bool isRunning() const = 0;

        [[nodiscard]] virtual double getGameTime() const = 0;

        [[nodiscard]] virtual float getFrameDelta() const = 0;

        virtual void closeGame() = 0;
    };
} // namespace Adagio

#endif // GL_ADAGIO_GAMESTATS_H

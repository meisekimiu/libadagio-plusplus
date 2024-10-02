#ifndef GL_ADAGIO_ACTIONSTATE_H
#define GL_ADAGIO_ACTIONSTATE_H

#include <vector>
#include "../keyboard/KeyboardState.h"
#include "../mouse/MouseState.h"
#include "../gamepad/GamepadCollection.h"
#include "ActionConstants.h"

namespace Adagio {

    class ActionState {
    public:
        void linkInput(KeyboardState *k);

        void linkInput(MouseState *m);

        void linkInput(GamepadCollection *g);

        [[nodiscard]] bool isActionDown(std::uint32_t name) const;

        [[nodiscard]] bool isActionUp(std::uint32_t name) const;

        [[nodiscard]] bool hasActionStarted(std::uint32_t name) const;

        [[nodiscard]] bool hasActionEnded(std::uint32_t name) const;

        Vector2f getActionDirection(std::uint32_t name) const;

        void registerActionButton(std::uint32_t name, Input::InputType inputType, std::uint16_t buttonId);

        void
        registerActionDirectionKeys(std::uint32_t name, Adagio::keycode left, Adagio::keycode down, Adagio::keycode up,
                                    Adagio::keycode right);

        void registerActionDirectionAxes(std::uint32_t name, std::uint32_t axisName);

        void update();

    private:
        struct ActionButtonEntry {
            Input::InputType type;
            std::uint16_t buttonId;
        };
        struct ActionDirectionKeys {
            std::uint16_t keys[4];
        };
        std::unordered_map<std::uint32_t, std::vector<ActionButtonEntry>> buttonDirectory;
        std::unordered_map<std::uint32_t, Input::ButtonBitState> buttons;

        std::unordered_map<std::uint32_t, std::vector<ActionDirectionKeys>> directionKeys;
        std::unordered_map<std::uint32_t, std::vector<std::uint32_t>> directionAxes;
        std::unordered_map<std::uint32_t, Vector2f> directions;

        KeyboardState *keyboard;
        MouseState *mouse;
        GamepadCollection *gamepad;

        void updateButtons();

        void updateDirections();
    };

} // Adagio

#endif //GL_ADAGIO_ACTIONSTATE_H

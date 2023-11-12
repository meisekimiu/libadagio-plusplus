#ifndef GL_ADAGIO_COLOR_H
#define GL_ADAGIO_COLOR_H

#include <string>

namespace Adagio {
    struct Color {
        unsigned char r = 0;
        unsigned char g = 0;
        unsigned char b = 0;
        unsigned char a = 255;

        [[nodiscard]] std::string toHex() const;

        static Color fromHexCode(std::string code);
    };
} // Adagio

#endif //GL_ADAGIO_COLOR_H

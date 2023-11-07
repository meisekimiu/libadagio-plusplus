#ifndef GL_ADAGIO_VECTOR2_H
#define GL_ADAGIO_VECTOR2_H

#include <string>
#include <ostream>
#include <sstream>

namespace Adagio {
    template<typename T>
    struct Vector2 {
        T x;
        T y;

        Vector2();

        Vector2(T x, T y);

        template<typename U>
        explicit Vector2(const Vector2<U> &vec);

        [[nodiscard]] double magnitude() const;

        [[nodiscard]] std::string to_string() const;

        [[nodiscard]] Vector2<T> normalized() const;

        [[nodiscard]] Vector2<T> floor() const;

        void clamp(const Vector2<T> &lower, const Vector2<T> &upper);
    };

    typedef Vector2<int> Vector2i;
    typedef Vector2<unsigned int> Vector2u;
    typedef Vector2<float> Vector2f;
    typedef Vector2<double> Vector2d;
}

#include "Vector2-impl.hpp"

#endif //GL_ADAGIO_VECTOR2_H

#ifndef GL_ADAGIO_RECT_H
#define GL_ADAGIO_RECT_H

#include "Vector2.h"
#include <array>

namespace Adagio {
template <typename T> struct Rect {
  Vector2<T> position;
  Vector2<T> size;

  Rect();

  Rect(Vector2<T> position, Vector2<T> size);

  Rect(T x, T y, T w, T h);

  template <typename U> explicit Rect(const Rect<U> &r);

  [[nodiscard]] T x() const;

  [[nodiscard]] T y() const;

  [[nodiscard]] T width() const;

  [[nodiscard]] T height() const;

  [[nodiscard]] Vector2<T> center() const;

  [[nodiscard]] const std::array<Vector2<T>, 4> corners() const;

  [[nodiscard]] std::string to_string() const;

  bool contains(Vector2<T> point) const;

  bool contains(Rect<T> rect) const;

  bool intersects(Rect<T> rect) const;

private:
  void correctNegativeSize();

  void correctNegativeValues(T &sizeVal, T &positionVal);
};

typedef Rect<int> RectI;
typedef Rect<unsigned int> RectU;
typedef Rect<float> RectF;
typedef Rect<double> RectD;
} // namespace Adagio

#include "Rect-impl.hpp"

#endif // GL_ADAGIO_RECT_H

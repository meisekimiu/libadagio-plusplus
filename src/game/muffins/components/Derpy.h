#ifndef GL_ADAGIO_DERPY_H
#define GL_ADAGIO_DERPY_H

#include "../../../math/Vector2.h"

namespace Muffins {
  struct Derpy {
    double t{0.0};
    double floatingFactor{50.0};
    double frequency{0.02};
    double baseY{205};
  };
}

#endif // GL_ADAGIO_DERPY_H

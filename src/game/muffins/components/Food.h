#ifndef GL_ADAGIO_FOOD_H
#define GL_ADAGIO_FOOD_H

namespace Muffins {
struct Food {
  double speed{1.0};
  bool canHitGround{false};
  unsigned char points{1};
};
}

#endif // GL_ADAGIO_FOOD_H

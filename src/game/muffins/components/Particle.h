#ifndef GL_ADAGIO_MUFFINCRUMB_H
#define GL_ADAGIO_MUFFINCRUMB_H

namespace Muffins {
  struct Particle {
    double xVel{0.0};
    double yVel{0.0};
    double angularVel{0.0};
    double lifeTime{3.141592654};
    double gravity{0.25};
    double time{0.0};
  };
}

#endif // GL_ADAGIO_MUFFINCRUMB_H

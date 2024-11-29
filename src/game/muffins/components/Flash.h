#ifndef GL_ADAGIO_FLASH_H
#define GL_ADAGIO_FLASH_H

namespace Muffins {
struct Flash {
  double visibleLifetime{0.08333333333};
  double lifetime{2.0};
  bool isMuffinFail{false};
};
}

#endif // GL_ADAGIO_FLASH_H

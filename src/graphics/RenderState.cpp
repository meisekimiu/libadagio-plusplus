#include "RenderState.h"

namespace Adagio {
bool RenderState::operator<(const RenderState &other) const {
  return zIndex < other.zIndex;
}
} // namespace Adagio

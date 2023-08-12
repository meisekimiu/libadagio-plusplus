#include "RenderState.h"

namespace Adagio {
    bool RenderState::operator<(const RenderState &other) {
        return zIndex < other.zIndex;
    }
}

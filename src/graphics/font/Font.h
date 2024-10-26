#ifndef GL_ADAGIO_FONT_H
#define GL_ADAGIO_FONT_H

#include "../../resource/Asset.h"

namespace Adagio {
    typedef unsigned char FontHandle;

    struct FontMetadata {
        int baseSize{12};
    };

    struct Font : public Asset<FontHandle, FontMetadata> {
        Font();

        Font(FontHandle handle, FontHandle secret);
    };
}


#endif //GL_ADAGIO_FONT_H

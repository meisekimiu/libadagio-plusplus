#include "Font.h"

Adagio::Font::Font() : Asset<FontHandle, FontMetadata>(0, 0, {}) {}

Adagio::Font::Font(Adagio::FontHandle handle, Adagio::FontHandle secret) :
        Asset<FontHandle, FontMetadata>(handle,
                                        secret,
                                        {}) {}

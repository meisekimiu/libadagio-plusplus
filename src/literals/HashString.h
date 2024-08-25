#ifndef GL_ADAGIO_HASHSTRING_H
#define GL_ADAGIO_HASHSTRING_H

#include <cstdint>
#include <string>
#include "CrcLookup.h"

namespace Adagio {
    static constexpr std::uint32_t crcLookupTable[256] = ADAGIO_CRC_LOOKUP;

    constexpr std::uint32_t crc(const char *str, size_t length) {
        std::uint32_t reg = 0;
        for (size_t i = 0; i < length + 4; i++) {
            std::uint8_t topByte = (reg >> 24) & 0xFF;
            std::uint8_t nextMsgByte = (i < length) ? str[i] : 0;
            reg = (reg << 8) | nextMsgByte;
            reg ^= crcLookupTable[topByte];
        }
        return reg;
    }
}

constexpr std::uint32_t operator ""_hs(const char *string, std::size_t size) {
    return Adagio::crc(string, size);
}

#endif // GL_ADAGIO_HASHSTRING_H

#include "Color.h"
#include <iomanip>
#include <ios>
#include <sstream>
#include <stdexcept>

static unsigned char getSingleHexDigit(const std::string &str, size_t pos) {
  return std::stoi(str.substr(pos, 1), nullptr, 16) * 0x11;
}

static unsigned char getDoubleHexDigits(const std::string &str, size_t pos) {
  return std::stoi(str.substr(pos, 2), nullptr, 16);
}

static unsigned char readHexDigit(const std::string &str, size_t pos) {
  if (pos == 3 && str.length() % 4 != 0) {
    return 255;
  }
  return str.length() < 6 ? getSingleHexDigit(str, pos)
                          : getDoubleHexDigits(str, pos * 2);
}

namespace Adagio {
Color Color::fromHexCode(std::string code) {
  std::string hexString = code[0] == '#' ? code.substr(1) : code;
  Color c{0, 0, 0, 255};
  if (hexString.length() != 3 && hexString.length() != 4 &&
      hexString.length() != 6 && hexString.length() != 8) {
    throw std::invalid_argument("Invalid number of hex digits for Color code");
  }
  c.r = readHexDigit(hexString, 0);
  c.g = readHexDigit(hexString, 1);
  c.b = readHexDigit(hexString, 2);
  c.a = readHexDigit(hexString, 3);
  return c;
}

std::string Color::toHex() const {
  unsigned int hexNum = 0;
  hexNum += r << 16;
  hexNum += g << 8;
  hexNum += b;
  std::stringstream ss;
  ss << "#" << std::setfill('0') << std::setw(sizeof(char) * 2) << std::hex
     << hexNum;
  if (a < 255) {
    ss << std::hex << static_cast<int>(a);
  }
  return std::string(ss.str());
}
} // namespace Adagio

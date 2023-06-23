#pragma once

#include <cstdint>

namespace milka
{
  static const float inv255f = 1.f/255.f;
  struct Color
  {
    std::uint8_t r, g, b;
  };
}

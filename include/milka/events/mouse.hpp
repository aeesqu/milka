#pragma once

#include <SDL2/SDL.h>
#include <cstdint>

namespace milka
{
  enum MouseButton : std::uint8_t
  {
    LEFT = 1,
    MIDDLE = 2,
    RIGHT = 3,
  };
}

#pragma once

#include "milka/graphics/color.hpp"

namespace milka
{
  struct Vertex
  {
    void operator=(const Vertex& other)
    {
      this->x = other.x;
      this->y = other.y;
      this->color.r = other.color.r;
      this->color.g = other.color.g;
      this->color.b = other.color.b;
    }

    int x, y;

    Color color;
  };
}

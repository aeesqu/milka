#pragma once

#include <cstdint>

#include "milka/graphics/vertex.hpp"

namespace milka
{
  struct VertexBuffer
  {
    VertexBuffer();
    VertexBuffer(std::uint32_t size);
    
    // Deleting vertexes
    ~VertexBuffer();

    // Setting the vertexes
    Vertex& operator[](std::uint32_t index);
    
    Vertex* getData();
    std::uint32_t getSize() const;
  private:
    Vertex* vertexes;
    std::uint32_t size;
  };
}

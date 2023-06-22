#include <cassert>

#include "milka/graphics/vertexBuffer.hpp"

namespace milka
{
  VertexBuffer::VertexBuffer()
  {
    this->size = 3;
    this->vertexes = new Vertex[this->size];
  }

  VertexBuffer::VertexBuffer(std::uint32_t size)
  {
    this->size = size;
    this->vertexes = new Vertex[this->size];
  }

  // Deleting vertexes
  VertexBuffer::~VertexBuffer()
  {
    delete[] this->vertexes;
  }

  // Setting the vertexes
  Vertex& VertexBuffer::operator[](std::uint32_t index)
  {
    assert(this->size > index);

    return this->vertexes[index];
  }
  
  Vertex* VertexBuffer::getData()
  {
    return this->vertexes;
  }

  std::uint32_t VertexBuffer::getSize() const
  {
    return this->size;
  }
}

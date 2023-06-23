#pragma once

#include <d3d9.h>

#include "milka/graphics/vertexBuffer.hpp"
#include "milka/graphics/d3d9/d3d9_vertex.hpp"

namespace milka
{
  // TODO: If the user create a lot of vertexes buffer
  // everytime, it'll start to slow the application.
  // this can be solve if the d3d9_VertexBuffer is created
  // when the user creates a VertexBuffer, but how'd I do
  // that? The vertex buffer should detect the current api?
  struct d3d9_VertexBuffer
  {
    d3d9_VertexBuffer(
        LPDIRECT3DDEVICE9 dev,
        VertexBuffer* vbuffer);

    ~d3d9_VertexBuffer();
    
    LPDIRECT3DVERTEXBUFFER9 getData() const;

  private:
    LPDIRECT3DVERTEXBUFFER9 d3d9_buffer_ptr;
  };
}

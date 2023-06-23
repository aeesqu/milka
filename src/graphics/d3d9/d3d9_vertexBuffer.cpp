#include "milka/graphics/d3d9/d3d9_vertexBuffer.hpp"
#include "milka/graphics/d3d9/d3d9_vertex.hpp"

namespace milka
{
  d3d9_VertexBuffer::d3d9_VertexBuffer(
      LPDIRECT3DDEVICE9 dev,
      VertexBuffer* vbuffer)
  {
    dev->CreateVertexBuffer(
      vbuffer->getSize()*sizeof(d3d9_Vertex),
      0,
      MILKA_D3D9_CUSTOM_FVF,
      D3DPOOL_MANAGED,
      &this->d3d9_buffer_ptr,
      NULL
    );

    d3d9_Vertex* pVoid;
    this->d3d9_buffer_ptr->Lock(0, 0, (void**) &pVoid, 0);
    for (auto i = 0; i < vbuffer->getSize(); i++)
    {
      d3d9_Vertex d3d9vertex((*vbuffer)[i]);
      *pVoid = d3d9vertex;
      pVoid++;
    }
    this->d3d9_buffer_ptr->Unlock();
  }

  d3d9_VertexBuffer::~d3d9_VertexBuffer()
  {
    this->d3d9_buffer_ptr->Release();
  }

  LPDIRECT3DVERTEXBUFFER9 d3d9_VertexBuffer::getData() const
  {
    return this->d3d9_buffer_ptr;
  }
}

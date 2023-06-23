#include "milka/graphics/d3d9/d3d9_vertex.hpp"

namespace milka
{
  d3d9_Vertex::d3d9_Vertex()
  {
    this->x = 0;
    this->y = 0;
    this->z = 1.f;
    this->color = D3DCOLOR_XRGB(0, 0, 0);
  }

  d3d9_Vertex::d3d9_Vertex(Vertex vertex)
  {
    this->x = vertex.x;
    this->y = vertex.y;
    this->z = 1.f;

    this->color = D3DCOLOR_XRGB(
        vertex.color.r, 
        vertex.color.g, 
        vertex.color.b);
  }
}

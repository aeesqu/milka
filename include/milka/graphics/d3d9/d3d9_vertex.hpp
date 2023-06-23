#pragma once

#include <d3dx9math.h>

#include "milka/graphics/vertex.hpp"

namespace milka
{
#define MILKA_D3D9_CUSTOM_FVF (D3DFVF_XYZ | D3DFVF_DIFFUSE)
    
  struct d3d9_Vertex
  {
    d3d9_Vertex();
    d3d9_Vertex(Vertex vertex);

    float x, y, z;
    DWORD color;
  };
}

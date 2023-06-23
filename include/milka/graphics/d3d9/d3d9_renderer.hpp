#pragma once

#include <d3d9.h>
#include <d3dx9.h>
#include <cstdint>
#include <windows.h>

#include "milka/graphics/renderer.hpp"
#include "milka/graphics/rendererInternal.hpp"

namespace milka
{
  struct d3d9_Renderer : RendererInternal
  {
  public:
    d3d9_Renderer();
    ~d3d9_Renderer() override;

    Result Init() override;
    
    void begin() override;
    void drawVertexBuffer(VertexBuffer& buffer) override;
    void end() override;
  private:
    LPDIRECT3DDEVICE9 dev;
    LPDIRECT3D9 d3d;
    IDirect3DVertexShader9* vshader;
    IDirect3DPixelShader9* pshader;
    
    const static int VERTEX_BUFFERS_SIZE = 10;
    IDirect3DVertexBuffer9* vertexBuffers[VERTEX_BUFFERS_SIZE];
    std::uint32_t vertexBufferSizes[VERTEX_BUFFERS_SIZE];
    std::uint32_t currentVertexBuffer;
  };
}

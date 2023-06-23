#include <iostream>
#include <d3dx9math.h>
#include <d3dcompiler.h>

#include "milka/graphics/d3d9/d3d9_renderer.hpp"
#include "milka/graphics/d3d9/d3d9_vertex.hpp"
#include "milka/graphics/d3d9/d3d9_vertexBuffer.hpp"
#include "milka/core/window.hpp"

namespace milka
{
  d3d9_Renderer::d3d9_Renderer()
  {

  }

  d3d9_Renderer::~d3d9_Renderer()
  {
    this->dev->Release();
    this->d3d->Release();
  }

  Result d3d9_Renderer::Init()
  {
    std::cout << "Initializing d3d9!\n";
    
    if (!this->window_ptr)
      std::cout << "window not defined\n";

    // TODO: Make something like: milka::Platform::Windows::getHandle(this->window_ptr.get());
    HWND hwnd = this->window_ptr->getHwnd();
    this->d3d = Direct3DCreate9(D3D_SDK_VERSION);
    D3DPRESENT_PARAMETERS d3dpp {0};
    d3dpp.Windowed = true;
    d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
    d3dpp.hDeviceWindow = hwnd;
    d3dpp.BackBufferFormat = D3DFMT_X8R8G8B8;
    d3dpp.BackBufferWidth = this->window_ptr->getWidth();
    d3dpp.BackBufferHeight = this->window_ptr->getHeight();

    this->d3d->CreateDevice(
        D3DADAPTER_DEFAULT,
        D3DDEVTYPE_HAL,
        hwnd,
        D3DCREATE_SOFTWARE_VERTEXPROCESSING,
        &d3dpp,
        &this->dev);

    D3DCAPS9 deviceCaps {};
    this->dev->GetDeviceCaps(&deviceCaps);
    if (deviceCaps.VertexShaderVersion < D3DVS_VERSION(3, 0))
      std::cout << "HLSL Vertex shader 3.0 is not supported in your machine\n";
    if (deviceCaps.PixelShaderVersion < D3DPS_VERSION(2, 0))
      std::cout << "HLSL Pixel shader 2.0 is not supported in your machine\n";
    
    for (auto i = 0; i < d3d9_Renderer::VERTEX_BUFFERS_SIZE; i++) {
      this->vertexBuffers[i] = nullptr;
      this->vertexBufferSizes[i] = 0;
    }

    this->currentVertexBuffer = 0;
    
    // ---------------------
    // CREATING VERTEX SHADER
    // ---------------------
    
    const char* shader_str = R"(
    
    float4x4 transf : register(c0);
    
    struct VS_Input
    {
      float4 vPos  : POSITION;
      float4 vColor: COLOR;
    };

    struct VS_Output
    {
      float4 vPos  : POSITION;
      float4 vColor: COLOR;
    };

    VS_Output VS_Main(VS_Input inp)
    {
      VS_Output vout;
      vout.vPos = inp.vPos;
      
      vout.vPos = mul(transf, vout.vPos);

      vout.vColor = inp.vColor;

      return vout;
    }
    
    float4 PS_Main(float4 input : COLOR) : COLOR
    {
      return input;
    }
    )";

    ID3DBlob* vsBlob;
    ID3DBlob* psBlob;

    D3DCompile((void*)shader_str, strlen(shader_str), "vshder", NULL, NULL,
        "VS_Main", "vs_2_0", NULL, NULL, &vsBlob, NULL);
    D3DCompile((void*)shader_str, strlen(shader_str), "vshder", NULL, NULL,
        "PS_Main", "ps_2_0", NULL, NULL, &psBlob, NULL);
    
    if (!vsBlob) {
      std::cout << "Error compiling vertex shader\n";
    }
    if (!psBlob) {
      std::cout << "Error compiling pixel shader\n";
    }

    this->dev->CreateVertexShader((DWORD*)vsBlob->GetBufferPointer(), &this->vshader);
    this->dev->CreatePixelShader((DWORD*)psBlob->GetBufferPointer(), &this->pshader);
  
    if (!this->vshader) {
      std::cout << "Couldn't create vertex shader\n";
    }
    if (!this->pshader) {
      std::cout << "Couldn't create pixel shader\n";
    }

    return Result::Success();
  }

  void d3d9_Renderer::begin()
  {
    D3DVIEWPORT9 vp;
    vp.X = 0;
    vp.Y = 0;
    vp.Width = this->window_ptr->getWidth();
    vp.Height = this->window_ptr->getHeight();
    vp.MinZ = 0.f;
    vp.MaxZ = 1.f;
    
    this->dev->SetViewport(&vp);

    this->dev->Clear(0, NULL, D3DCLEAR_TARGET, 
        D3DCOLOR_XRGB(this->br, this->bb, this->bg), 1.f, 0);
    
    D3DXMATRIX d3dmatrix {0};
    d3dmatrix.m[0][0] = 2.0f / this->window_ptr->getWidth();
    d3dmatrix.m[1][1] = -2.0f / this->window_ptr->getHeight();
    d3dmatrix.m[2][2] = 1.0f;
    d3dmatrix.m[3][0] = -1.0f;
    d3dmatrix.m[3][1] = 1.0f;
    d3dmatrix.m[3][3] = 1.0f;
    
    this->dev->SetVertexShaderConstantF(0, (float*)&d3dmatrix, 4);

    this->dev->SetVertexShader(this->vshader);
    this->dev->SetPixelShader(this->pshader);

    this->dev->SetFVF(MILKA_D3D9_CUSTOM_FVF);
    
    this->dev->BeginScene();
  }
  
  void d3d9_Renderer::drawVertexBuffer(VertexBuffer& buffer)
  {
    // TODO: Handle d9 errors
    const std::uint32_t vboidx = this->currentVertexBuffer;

    IDirect3DVertexBuffer9* vbo = this->vertexBuffers[vboidx];
    
    // If the current vertex buffer size is smaller than the required size
    if (this->vertexBufferSizes[vboidx] < buffer.getSize()) {
      if (vbo) {
        IDirect3DVertexBuffer9_Release(vbo);
      }

      this->dev->CreateVertexBuffer(
          buffer.getSize()*sizeof(d3d9_Vertex),
          0,
          MILKA_D3D9_CUSTOM_FVF,
          D3DPOOL_MANAGED,
          &vbo,
          NULL);
      
      if (!vbo) {
        std::cout << "Something went wrong, my bro\n";
      } else {
        std::cout << "Vertex buffer created.\n";
      }
       
      this->vertexBuffers[vboidx] = vbo;
      this->vertexBufferSizes[vboidx] = buffer.getSize();
    }

    if (vbo) {
      d3d9_Vertex* data_ptr;

      vbo->Lock(0, 0, (void**) &data_ptr, 0);
      for (auto i = 0; i < buffer.getSize(); i++) {
        d3d9_Vertex d3d9vertex(buffer[i]);
        *data_ptr = d3d9vertex;
        data_ptr++;
      }
      vbo->Unlock();
    }
    
    this->currentVertexBuffer++;
    if (this->currentVertexBuffer >= d3d9_Renderer::VERTEX_BUFFERS_SIZE)
      this->currentVertexBuffer = 0;
    
    //D3DXMATRIX world {0};
    //D3DXMatrixIdentity(&world);

    //D3DXMatrixRotationZ(&world, 3.141592*0.25);

    this->dev->SetStreamSource(0, vbo, 0, sizeof(d3d9_Vertex));
    this->dev->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, buffer.getSize()-2);
  }

  void d3d9_Renderer::end()
  {
    this->dev->EndScene();
    this->dev->Present(NULL, NULL, NULL, NULL);
  }
}

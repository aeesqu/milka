#include "milka/core/window.hpp"
#include "milka/graphics/renderer.hpp"
#include "milka/graphics/d3d9/d3d9_renderer.hpp"

namespace milka
{
  RendererDescriptor::RendererDescriptor()
  {
    this->vsync = false;
    this->api = RendererAPI::SDL2Renderer;
  }

  Renderer::Renderer()
    : descriptor(new RendererDescriptor())
  {
  }

  Renderer::~Renderer() {}
 
  RendererDescriptor* Renderer::GetDescriptor()
  {
    return this->descriptor.get();
  }
  
  RendererInternal* Renderer::GetInternal()
  {
    return this->rendererInternal.get();
  }

  Result Renderer::Init(std::shared_ptr<Window> window_ptr)
  {
    Result res;
    
    switch (this->descriptor->api)
    {
      case RendererAPI::DirectX9: {
        this->rendererInternal = std::make_unique<d3d9_Renderer>();
        break;
      }
      case RendererAPI::SDL2Renderer: {
        //this->rendererInternal = SDL2_Renderer(this->descriptor);
        break;
      }
      default:
        break;
    }
    
    this->window_ptr = window_ptr;

    this->rendererInternal->descriptor = std::move(this->descriptor);
    this->rendererInternal->window_ptr = this->window_ptr;
    res = this->rendererInternal->Init();
   
    return res;
  }
}

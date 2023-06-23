#pragma once

#include <memory>

#include "milka/core/logging.hpp"

namespace milka
{
  // Supported renderer APIs for now.
  enum RendererAPI
  {
    DirectX9,
    SDL2Renderer,
  };

  struct RendererDescriptor
  {
    bool vsync;
    RendererAPI api;
    
    RendererDescriptor();
  };
  
  struct RendererInternal;
  struct Window;

  struct Renderer
  {
  private:
    // After being initialized, internal renderer
    // will own it.
    std::unique_ptr<RendererDescriptor> descriptor;

    // Interface for internal renderer that contains the
    // implementation for the choosen api
    std::unique_ptr<RendererInternal> rendererInternal;

    // Pointer to window
    std::shared_ptr<Window> window_ptr;
  public:
    Renderer();
    ~Renderer();

    RendererDescriptor* GetDescriptor();
    
    RendererInternal* GetInternal();

    Result Init(std::shared_ptr<Window> window_ptr);
  };
}

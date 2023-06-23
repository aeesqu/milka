#pragma once

#include <memory>
#include <string>

#include "milka/core/logging.hpp"
#include "milka/graphics/renderer.hpp"
#include "milka/graphics/vertexBuffer.hpp"

namespace milka
{
  struct Window;
  struct RendererDescriptor;
  
  // Interface that all renderers uses.
  struct RendererInternal
  {
    friend Renderer;
  protected:
    // Descriptor wil be set by renderer class
    std::unique_ptr<RendererDescriptor> descriptor;
    
    // Window ptr will be set by renderer class
    std::shared_ptr<Window> window_ptr;
    
    // Vertical syncronization
    bool vsync;

    // The choosen renderer api
    enum RendererAPI api;
    
    // TODO: Remove
    int br, bg, bb;
  public:
    RendererInternal();
    virtual ~RendererInternal();

    virtual Result Init();

    void setBackgroundColor(int r, int g, int b);
    
    virtual void begin();
    virtual void drawVertexBuffer(VertexBuffer& buffer);
    virtual void end();
  };
}

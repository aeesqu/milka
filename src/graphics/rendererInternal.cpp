#include "milka/graphics/rendererInternal.hpp"

namespace milka
{
  RendererInternal::RendererInternal()
      : br(50), bg(50), bb(50)
  {

  }

  RendererInternal::~RendererInternal()
  {

  }

  Result RendererInternal::Init()
  {
    this->vsync = this->descriptor->vsync;
    this->api = this->descriptor->api;
    
    return Result::Success();
  }
  
  void RendererInternal::setBackgroundColor(int r, int g, int b)
  {
    this->br = r;
    this->bg = g;
    this->bb = b;
  }
  void RendererInternal::begin() {}
  void RendererInternal::drawVertexBuffer(VertexBuffer& buffer) {}
  void RendererInternal::end() {}
}

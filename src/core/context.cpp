#include "milka/core/context.hpp"
#include "milka/core/window.hpp"
#include "milka/graphics/renderer.hpp"
#include "milka/events/event.hpp"

namespace milka
{
  WindowDescriptor* Context::GetWindowDescriptor()
  {
    return this->window_ptr->GetDescriptor();
  }

  RendererDescriptor* Context::GetRendererDescriptor()
  {
    return this->renderer_ptr->GetDescriptor();
  }

  Event* Context::GetEvent()
  {
    return this->event_ptr.get();
  }
  
  Renderer* Context::GetRenderer()
  {
    return this->renderer_ptr.get();
  }

  Result Context::Start()
  {
    Result wres = this->window_ptr->Init();
    Result rres = this->renderer_ptr->Init(this->window_ptr);

    return Result::Success();
  }
  
  Context::Context()
    : window_ptr(new Window()),
      renderer_ptr(new Renderer()),
      event_ptr(new Event())
  {
   
  }

  Context::~Context()
  {

  }
}

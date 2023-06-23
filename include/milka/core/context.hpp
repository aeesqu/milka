#pragma once

#include <memory>
#include <string>

#include "milka/core/logging.hpp"

namespace milka
{
  struct WindowDescriptor;
  struct RendererDescriptor;
  struct Window;
  struct Renderer;
  struct Event;

  struct Context
  {
  public:  
    // Window will be shared with renderer, so It's
    // defined as shared_ptr
    std::shared_ptr<Window> window_ptr;

    // Other ones are unique_ptr
    std::unique_ptr<Renderer> renderer_ptr;
    std::unique_ptr<Event> event_ptr;

    WindowDescriptor* GetWindowDescriptor();
    RendererDescriptor* GetRendererDescriptor();

    Event* GetEvent();
    Renderer* GetRenderer();

    Context();
    ~Context();

    Result Start();
  };
}

#include <SDL2/SDL.h>
#include <SDL2/SDL_syswm.h>

#include "milka/core/window.hpp"

namespace milka
{
  WindowDescriptor::WindowDescriptor()
  {
    this->title = "milka engine!";
    this->width = 800;
    this->height = 600;
  }

  Window::Window()
    : descriptor(new WindowDescriptor()),
      sdl_window_ptr(nullptr)
  {
  }

  Window::~Window()
  {
    if (this->sdl_window_ptr)
      SDL_DestroyWindow(this->sdl_window_ptr);
  }

  WindowDescriptor* Window::GetDescriptor()
  {
    return this->descriptor.get();
  }

  Result Window::Init()
  {
    this->title = this->descriptor->title;
    this->width = this->descriptor->width;
    this->height = this->descriptor->height;

    this->sdl_window_ptr = SDL_CreateWindow(this->title.c_str(),
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        this->width, this->height,
        0);
    if (!this->sdl_window_ptr)
      return Result::Error(1, "Couldn't create sdl window.");
    
    return Result::Success();
  }
  HWND Window::getHwnd()
  {
    SDL_SysWMinfo wmInfo;
    SDL_VERSION(&wmInfo.version);
    SDL_GetWindowWMInfo(this->sdl_window_ptr, &wmInfo);

    return wmInfo.info.win.window;
  }

  int Window::getWidth() const
  {
    return this->width;
  }

  int Window::getHeight() const
  {
    return this->height;
  } 
}

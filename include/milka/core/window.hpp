#pragma once

#include <SDL2/SDL.h>
#include <memory>
#include <string>
#include <windows.h>

#include "milka/core/logging.hpp"

namespace milka
{
  struct WindowDescriptor
  {
    std::string title;
    int width, height;
    
    WindowDescriptor();
  };

  struct Window
  {
  private:
    std::string title;
    int width, height;
  
    SDL_Window* sdl_window_ptr;
  
    // Used for initialize window, only.
    std::unique_ptr<WindowDescriptor> descriptor;
  public:
    Window();
    ~Window();
    
    WindowDescriptor* GetDescriptor();

    Result Init();

    HWND getHwnd();

    int getWidth() const;
    int getHeight() const;
  };
}

#pragma once

#include "milka/graphics/renderer.hpp"
#include "milka/graphics/rendererInternal.hpp"

namespace milka
{
  struct sdl2_Renderer
  {
  private:
    SDL_Renderer* sdl_renderer_ptr;
    SDL_Window* sdl_window_ptr;
  public:
    sdl2_Renderer();
    ~sdl2_Renderer();

    Result Init() override;
  };
}

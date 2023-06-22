#include <SDL2/SDL.h>
#include <string.h>

#include "milka/events/event.hpp"

namespace milka
{
  Event::Event()
  {
    this->sdl_keystate_ptr = SDL_GetKeyboardState(NULL);
    this->old_keystate = (Uint8*) malloc(256*sizeof(std::uint8_t));
    memcpy(this->old_keystate, this->sdl_keystate_ptr, 256*sizeof(std::uint8_t));
  }

  Event::~Event()
  {
    free(this->old_keystate);
  }
  
  void Event::update_events()
  {
    memcpy(this->old_keystate, this->sdl_keystate_ptr, 256*sizeof(std::uint8_t));
      
    this->event_types.reset();

    SDL_Event e;
    while (SDL_PollEvent(&e))
    {
      switch (e.type)
      {
        case SDL_QUIT:
          this->event_types.set(EventType::QUIT);
          break;
        case SDL_KEYDOWN:
          this->event_types.set(EventType::KEY_PRESS);
          break;
        case SDL_KEYUP:
          this->event_types.set(EventType::KEY_RELEASE);
          break;
        case SDL_MOUSEBUTTONDOWN:
          this->event_types.set(EventType::MOUSE_PRESS);
          break;
        case SDL_MOUSEBUTTONUP:
          this->event_types.set(EventType::MOUSE_RELEASE);
          break;
      }
    }

    std::uint32_t mask = SDL_GetMouseState(nullptr, nullptr);
    this->old_mouse_buttons = this->mouse_buttons;
    this->mouse_buttons.reset();
    
    if ((mask & SDL_BUTTON(MouseButton::LEFT)) == SDL_BUTTON(MouseButton::LEFT))
      this->mouse_buttons.set(MouseButton::LEFT);
    if ((mask & SDL_BUTTON(MouseButton::RIGHT)) == SDL_BUTTON(MouseButton::RIGHT))
      this->mouse_buttons.set(MouseButton::RIGHT);
    if ((mask & SDL_BUTTON(MouseButton::MIDDLE)) == SDL_BUTTON(MouseButton::MIDDLE))
      this->mouse_buttons.set(MouseButton::MIDDLE);
  }
  
  bool Event::contains(milka::EventType type)
  {
    return this->event_types.test(type);
  }

  bool Event::has_key(milka::KeyCode key)
  {
    return this->sdl_keystate_ptr[key] || this->old_keystate[key];
  }

  bool Event::key_up(milka::KeyCode key)
  {
    return !this->sdl_keystate_ptr[key];
  } 

  bool Event::key_down(milka::KeyCode key)
  {
    return this->sdl_keystate_ptr[key];
  }

  bool Event::key_released(milka::KeyCode key)
  {
    return this->old_keystate[key] && !this->sdl_keystate_ptr[key];
  }

  bool Event::key_pressed(milka::KeyCode key)
  {
    return !this->old_keystate[key] && this->sdl_keystate_ptr[key];
  } 
  
  int Event::get_mouse_x()
  {
    int x;
    SDL_GetMouseState(&x, nullptr);
    return x;
  }

  int Event::get_mouse_y()
  {
    int y;
    SDL_GetMouseState(nullptr, &y);
    return y;
  }

  bool Event::has_button(milka::MouseButton button)
  {
    return this->mouse_buttons.test(button) || 
      this->old_mouse_buttons.test(button);
  }

  bool Event::button_up(milka::MouseButton button)
  {
    return !this->mouse_buttons.test(button);
  }

  bool Event::button_down(milka::MouseButton button)
  {
    return this->mouse_buttons.test(button);
  }

  bool Event::button_released(milka::MouseButton button)
  {
    return this->old_mouse_buttons.test(button) && 
      !this->mouse_buttons.test(button);
  }

  bool Event::button_pressed(milka::MouseButton button)
  {
    return !this->old_mouse_buttons.test(button) &&
      this->mouse_buttons.test(button);
  }
}

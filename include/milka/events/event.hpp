#pragma once

#include <bitset>

#include "milka/events/keys.hpp"
#include "milka/events/mouse.hpp"

namespace milka
{
  enum EventType : std::uint8_t
  {
    QUIT = 0,
    WINDOW_RESIZED,
    KEY_PRESS,
    KEY_RELEASE,
    MOUSE_PRESS,
    MOUSE_RELEASE
  };

  struct Event
  {
  public:
    Event();
    ~Event();
    
    void update_events();
    
    bool contains(milka::EventType type);
    
    // Keyboard events
    bool has_key(milka::KeyCode key);
    bool key_up(milka::KeyCode key);
    bool key_down(milka::KeyCode key);
    bool key_released(milka::KeyCode key);
    bool key_pressed(milka::KeyCode key);
    
    // Mouse events
    int get_mouse_x();
    int get_mouse_y();
    bool has_button(milka::MouseButton button);
    bool button_up(milka::MouseButton button);
    bool button_down(milka::MouseButton button);
    bool button_released(milka::MouseButton button);
    bool button_pressed(milka::MouseButton button);
  private:
    // The keyboard state
    const Uint8* sdl_keystate_ptr;
    Uint8* old_keystate;
    
    // The mouse state
    std::bitset<4> mouse_buttons;
    std::bitset<4> old_mouse_buttons;
    
    // Bitset containing the event types
    std::bitset<6> event_types; 
  };
}

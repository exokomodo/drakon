#include "drakon/event.h"

std::optional<drakon::Event> drakon::Event::fromSDL(const SDL_Event &event) {
  switch (event.type) {
  case SDL_EVENT_QUIT: {
    const auto expected = drakon::QuitEvent::fromSDL(event);
    return expected.has_value()
               ? std::make_optional<drakon::Event>(expected.value())
               : std::nullopt;
  } break;
  case SDL_EVENT_KEY_DOWN:
  case SDL_EVENT_KEY_UP: {
    const auto expected = drakon::KeyEvent::fromSDL(event);
    return expected.has_value()
               ? std::make_optional<drakon::Event>(expected.value())
               : std::nullopt;
  } break;
  default:
    return std::nullopt;
  }
}

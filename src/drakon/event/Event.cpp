#include <drakon/event>
#include <drakon/input>

#ifdef DRAKON_SDL
std::optional<drakon::event::Event>
drakon::event::Event::fromSDL(const SDL_Event &event) {
  switch (event.type) {
  case SDL_EVENT_QUIT:
    return drakon::event::Event(Quit);
  case SDL_EVENT_KEY_DOWN:
    return drakon::event::Event(
        KeyDown, static_cast<drakon::input::InputType>(event.key.key));
  case SDL_EVENT_KEY_UP:
    return drakon::event::Event(
        KeyUp, static_cast<drakon::input::InputType>(event.key.key));
  default:
    return std::nullopt;
  }
}
#endif

drakon::event::Event::Event(const drakon::event::EventType _type)
    : type(_type) {}

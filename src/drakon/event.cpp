#include <drakon/event>

#ifdef DRAKON_SDL
drakon::event::Event drakon::event::Event::fromSDL(const SDL_Event &event) {
  switch (event.type) {
  case SDL_EVENT_QUIT:
    return drakon::event::Event(Quit);
  case SDL_EVENT_KEY_DOWN:
    return drakon::event::Event(
        KeyDown,
        KeyEventData(static_cast<drakon::input::InputType>(event.key.key)));
  case SDL_EVENT_KEY_UP:
    return drakon::event::Event(
        KeyUp,
        KeyEventData(static_cast<drakon::input::InputType>(event.key.key)));
  default:
    return drakon::event::Event(drakon::event::None);
  }
}
#endif

bool drakon::event::Event::isNone() { return type == None; }
bool drakon::event::Event::isKey() { return type == KeyUp || type == KeyDown; }
bool drakon::event::Event::isMouse() {
  return type == MouseClick || type == MouseDoubleClick ||
         type == MouseRightClick || type == MouseMove ||
         type == MouseScrollUp || type == MouseScrollDown;
}
bool drakon::event::Event::isWindow() {
  return type == WindowResize || type == WindowClose;
}
bool drakon::event::Event::isApplication() { return type == Quit; }
bool drakon::event::Event::isCustom() {
  return !(type == None || isKey() || isMouse() || isWindow() ||
           isApplication());
}
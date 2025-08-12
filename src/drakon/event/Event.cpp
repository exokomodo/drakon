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

const std::weak_ptr<drakon::event::KeyEventData>
drakon::event::Event::asKey() const {
  return static_pointer_cast<drakon::event::KeyEventData>(data);
}
const std::weak_ptr<drakon::event::MouseEventData>
drakon::event::Event::asMouse() const {
  return static_pointer_cast<drakon::event::MouseEventData>(data);
}
const std::weak_ptr<drakon::event::WindowEventData>
drakon::event::Event::asWindow() const {
  return static_pointer_cast<drakon::event::WindowEventData>(data);
}
const std::weak_ptr<drakon::event::ApplicationEventData>
drakon::event::Event::asApplication() const {
  return static_pointer_cast<drakon::event::ApplicationEventData>(data);
}

bool drakon::event::Event::isNone() const { return type == None; }
bool drakon::event::Event::isKey() const {
  return type == KeyUp || type == KeyDown;
}
bool drakon::event::Event::isMouse() const {
  return type == MouseClick || type == MouseDoubleClick ||
         type == MouseRightClick || type == MouseMove ||
         type == MouseScrollUp || type == MouseScrollDown;
}
bool drakon::event::Event::isWindow() const {
  return type == WindowResize || type == WindowClose;
}
bool drakon::event::Event::isApplication() const { return type == Quit; }
bool drakon::event::Event::isCustom() const {
  return !(type == None || isKey() || isMouse() || isWindow() ||
           isApplication());
}
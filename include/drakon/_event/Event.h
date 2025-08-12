#pragma once

#ifdef DRAKON_SDL
#include <SDL3/SDL.h>
#endif

#include <drakon/_event/EventType.h>

#include <any>
#include <optional>
#include <unordered_map>

namespace drakon::event {
struct Event {
  Event(const EventType _type);
  template <typename T>
  Event(const EventType _type, const T _data) : type(_type), data(_data) {}
  ~Event() = default;

  const EventType type;

#ifdef DRAKON_SDL
  static std::optional<Event> fromSDL(const SDL_Event &event);
#endif

  template <typename T> std::optional<T> getData() {
    if (data.has_value() && data.type() == typeid(T)) {
      return std::any_cast<T>(data);
    }
    return std::nullopt;
  }
  template <typename T> void setData(T _data) { data = _data; }

private:
  const std::any data;
};
} // namespace drakon::event

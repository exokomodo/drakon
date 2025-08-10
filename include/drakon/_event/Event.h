#pragma once

#ifdef DRAKON_SDL
#include <SDL3/SDL.h>
#endif

#include <drakon/_event/ApplicationEventData.h>
#include <drakon/_event/EventType.h>
#include <drakon/_event/IEventData.h>
#include <drakon/_event/KeyEventData.h>
#include <drakon/_event/MouseEventData.h>
#include <drakon/_event/WindowEventData.h>

#include <any>
#include <drakon/error>
#include <drakon/input>
#include <expected>
#include <memory>
#include <optional>
#include <string_view>

namespace drakon::event {
struct Event {
  const EventType type;
  const std::shared_ptr<IEventData> data;
#ifdef DRAKON_SDL
  static Event fromSDL(const SDL_Event &event);
#endif
  bool isNone() const;
  bool isKey() const;
  bool isMouse() const;
  bool isWindow() const;
  bool isApplication() const;
  bool isCustom() const;

  const std::shared_ptr<KeyEventData> asKey() const;
  const std::shared_ptr<MouseEventData> asMouse() const;
  const std::shared_ptr<WindowEventData> asWindow() const;
  const std::shared_ptr<ApplicationEventData> asApplication() const;

  template <typename T> auto asCustom() {
    static_assert(std::is_base_of_v<CustomEventData, T>,
                  "T must inherit from CustomEventData");
    return static_pointer_cast<T>(data);
  }

  template <typename T>
  Event(const EventType _type, T &&_data)
      : type(_type),
        data(std::make_shared<std::decay_t<T>>(std::forward<T>(_data))) {
    static_assert(std::is_base_of_v<IEventData, std::decay_t<T>>,
                  "T must inherit from EventData");
  }
  Event(const EventType _type, std::shared_ptr<IEventData> _data)
      : type(_type), data(_data) {}
  Event(const EventType _type) : type(_type) {}
  Event(const Event &other) : type(other.type), data(other.data) {}
  ~Event() = default;
};
} // namespace drakon::event

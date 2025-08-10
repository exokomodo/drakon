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
  bool isNone();
  bool isKey();
  bool isMouse();
  bool isWindow();
  bool isApplication();
  bool isCustom();

  auto asKey() { return static_pointer_cast<KeyEventData>(data); }
  auto asMouse() { return static_pointer_cast<MouseEventData>(data); }
  auto asWindow() { return static_pointer_cast<WindowEventData>(data); }
  auto asApplication() {
    return static_pointer_cast<ApplicationEventData>(data);
  }

  template <typename T> auto asCustom() {
    static_assert(std::is_base_of_v<CustomEventData, T>,
                  "T must inherit from CustomEventData");
    return static_pointer_cast<T>(data);
  }

  template <typename T>
  Event(const EventType _type, T &&_data)
      : type(_type),
        data(std::make_shared<std::decay_t<T>>(std::forward<T>(_data))) {
    static_assert(std::is_base_of_v<EventData, std::decay_t<T>>,
                  "T must inherit from EventData");
  }
  Event(const EventType _type, std::shared_ptr<IEventData> _data)
      : type(_type), data(_data) {}
  Event(const EventType _type) : type(_type) {}
  Event(const Event &other) : type(other.type), data(other.data) {}
  ~Event() = default;
};

// Keyboard events
static const EventType KeyUp = 0x6552B368;
static const EventType KeyDown = 0x46C6038E;
// Mouse events
static const EventType MouseClick = 0x270FB96E;
static const EventType MouseDoubleClick = 0x0D918A5B;
static const EventType MouseRightClick = 0x176F1014;
static const EventType MouseMove = 0x29F31CAE;
static const EventType MouseScrollUp = 0xD60370E3;
static const EventType MouseScrollDown = 0xF3454499;
// Window events
static const EventType WindowResize = 0x778E2279;
static const EventType WindowClose = 0xDB2B2610;
// Application events
static const EventType Quit = 0xBFB0B536;
} // namespace drakon::event

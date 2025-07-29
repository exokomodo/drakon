#pragma once

#include <SDL3/SDL.h>

#include <drakon/error.h>
#include <expected>
#include <optional>
#include <string_view>

namespace drakon {
// NOTE: When making an event, generate a GUID and take the front bits
typedef unsigned long EventType;

struct Event {
  virtual ~Event() {}
  const EventType &getType() const { return type; }
  virtual const std::string_view getName() const { return "Event"; };

  static std::optional<Event> fromSDL(const SDL_Event &event);

protected:
  EventType type;
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

struct QuitEvent : public Event {
  QuitEvent() { type = Quit; }
  const std::string_view getName() const override { return "QuitEvent"; }

  static const std::expected<QuitEvent, Error> fromSDL(const SDL_Event &event) {
    if (event.type == SDL_EVENT_QUIT) {
      return QuitEvent();
    }
    return std::unexpected(Error("Invalid SDL event type for QuitEvent"));
  }
};

struct KeyEvent : public Event {
  KeyEvent(EventType _type, const unsigned int _keyCode) : keyCode(_keyCode) {
    type = _type;
  }
  const std::string_view getName() const override { return "KeyEvent"; }
  unsigned int getKeyCode() const { return keyCode; }

  static const std::expected<KeyEvent, Error> fromSDL(const SDL_Event &event) {
    switch (event.type) {
    case SDL_EVENT_KEY_DOWN:
      return KeyEvent(KeyDown, event.key.key);
    case SDL_EVENT_KEY_UP:
      return KeyEvent(KeyUp, event.key.key);
    default:
      return std::unexpected(Error("Invalid SDL event type for KeyEvent"));
    }
  }

private:
  const unsigned int keyCode;
};
} // namespace drakon

#pragma once

#ifdef DRAKON_SDL
#include <SDL3/SDL.h>
#endif
#include <drakon/_system/ISystem.h>
#include <drakon/error>
#include <drakon/event>
#include <functional>
#include <map>
#include <optional>
#include <queue>
#include <vector>

#define MAKE_LISTENER(name)                                                    \
  std::function<void(drakon::event::Event)> name = [this](                     \
      drakon::event::Event event)

namespace drakon::system {
struct EventSystem : public ISystem {
  typedef std::function<void(drakon::event::Event)> Listener;

  EventSystem();
  EventSystem(const EventSystem &) = default;
  EventSystem(EventSystem &&) = default;
  EventSystem &operator=(const EventSystem &) = default;
  EventSystem &operator=(EventSystem &&) = default;
  ~EventSystem() = default;

  std::optional<drakon::error::Error> enqueue(drakon::event::Event event);
  std::optional<drakon::error::Error>
  addListener(const drakon::event::EventType type, Listener listener);
  bool removeListener(const drakon::event::EventType type, Listener listener);
  std::optional<drakon::error::Error> process() override;

private:
  typedef std::vector<Listener> EventListenerList;
  typedef std::map<drakon::event::EventType, EventListenerList>
      EventListenerMap;
  std::queue<drakon::event::Event> eventQueue;
  EventListenerMap listeners;

  bool isEmpty() const;
};
} // namespace drakon::system

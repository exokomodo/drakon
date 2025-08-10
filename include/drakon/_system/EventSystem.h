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

namespace drakon::system {
#define MAKE_LISTENER(name)                                                    \
  drakon::system::EventSystem::Listener name = [this](                         \
      drakon::event::Event event)

struct EventSystem : public ISystem {
  EventSystem();
  EventSystem(const EventSystem &) = default;
  EventSystem(EventSystem &&) = default;
  EventSystem &operator=(const EventSystem &) = default;
  EventSystem &operator=(EventSystem &&) = default;
  ~EventSystem() = default;

  typedef std::function<void(drakon::event::Event)> Listener;

  static EventSystem *getInstance();

  std::optional<drakon::error::Error> enqueue(drakon::event::Event event);
  std::optional<drakon::error::Error>
  addListener(const drakon::event::EventType type, Listener listener);
  bool removeListener(const drakon::event::EventType type, Listener listener);
  std::optional<drakon::error::Error> process() override;

private:
  static EventSystem *instance;

  typedef std::vector<Listener> ListenerList;
  typedef std::map<drakon::event::EventType, ListenerList> ListenerMap;
  std::queue<drakon::event::Event> eventQueue;
  ListenerMap listeners;

  bool isEmpty() const;
};
} // namespace drakon::system

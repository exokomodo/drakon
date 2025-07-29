#pragma once

#include <SDL3/SDL.h>
#include <drakon/error.h>
#include <drakon/event.h>
#include <drakon/system/interface.h>
#include <functional>
#include <map>
#include <optional>
#include <queue>
#include <vector>

#define MAKE_LISTENER(name)                                                    \
  std::function<void(drakon::Event)> name = [this](drakon::Event event)

namespace drakon {
struct EventSystem : public System {
  typedef std::function<void(drakon::Event &)> Listener;

  EventSystem();
  EventSystem(const EventSystem &) = default;
  EventSystem(EventSystem &&) = default;
  EventSystem &operator=(const EventSystem &) = default;
  EventSystem &operator=(EventSystem &&) = default;
  ~EventSystem() = default;

  std::optional<Error> enqueue(const drakon::Event &event);
  std::optional<Error> addListener(const drakon::EventType type,
                                   Listener listener);
  bool removeListener(const EventType type, Listener listener);
  std::optional<Error> process() override;

private:
  typedef std::vector<Listener> EventListenerList;
  typedef std::map<drakon::EventType, EventListenerList> EventListenerMap;
  std::queue<drakon::Event> eventQueue;
  EventListenerMap listeners;

  bool isEmpty() const;
};
} // namespace drakon

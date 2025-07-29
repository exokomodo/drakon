#pragma once

#include <SDL3/SDL.h>
#include <drakon/error.h>
#include <drakon/system/interface.h>
#include <functional>
#include <map>
#include <optional>
#include <queue>
#include <vector>

#define MAKE_LISTENER(name)                                                    \
  std::function<void(SDL_Event)> name = [this](SDL_Event event)

namespace drakon {
struct EventSystem : public System {
  typedef std::function<void(SDL_Event)> Listener;

  EventSystem();
  EventSystem(const EventSystem &) = default;
  EventSystem(EventSystem &&) = default;
  EventSystem &operator=(const EventSystem &) = default;
  EventSystem &operator=(EventSystem &&) = default;
  ~EventSystem() = default;

  std::optional<Error> enqueue(const SDL_Event &event);
  std::optional<Error> addListener(const SDL_EventType type,
                                   std::function<void(SDL_Event)> listener);
  bool removeListener(const SDL_EventType type,
                      std::function<void(SDL_Event)> listener);
  std::optional<Error> process() override;

private:
  typedef std::vector<std::function<void(SDL_Event)>> EventListenerList;
  typedef std::map<SDL_EventType, EventListenerList> EventListenerMap;
  std::queue<SDL_Event> eventQueue;
  EventListenerMap listeners;

  bool isEmpty() const;
};
} // namespace drakon

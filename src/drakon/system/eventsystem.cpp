#include <drakon/system/eventsystem.h>

drakon::EventSystem::EventSystem() {
  eventQueue = std::queue<SDL_Event>(); // Initialize the event queue
}

std::optional<drakon::Error>
drakon::EventSystem::enqueue(const SDL_Event &event) {
  try {
    eventQueue.push(event);
  } catch (const std::exception &e) {
    return Error(e.what());
  }
  return std::nullopt;
}

std::optional<drakon::Error>
drakon::EventSystem::addListener(const SDL_EventType type,
                                 std::function<void(SDL_Event)> listener) {
  auto &vec = listeners[type];
  for (const auto &existing : vec) {
    if (existing.target_type() == listener.target_type() &&
        existing.target<void(SDL_Event)>() ==
            listener.target<void(SDL_Event)>()) {
      return Error("Listener already registered for this event type.");
    }
  }
  vec.push_back(listener);
  return std::nullopt;
}

const bool
drakon::EventSystem::removeListener(const SDL_EventType type,
                                    std::function<void(SDL_Event)> listener) {
  auto it = listeners.find(type);
  if (it != listeners.end()) {
    auto &list = it->second;
    for (auto it = list.begin(); it != list.end(); ++it) {
      const auto &existing = *it;
      if (existing.target_type() == listener.target_type() &&
          existing.target<void(SDL_Event)>() ==
              listener.target<void(SDL_Event)>()) {
        list.erase(it);
        return true;
      }
    }
  }
  return false;
}

std::optional<drakon::Error> drakon::EventSystem::process() {
  // Process all events in the queue and notify listeners.
  while (!eventQueue.empty()) {
    SDL_Event event = eventQueue.front();
    eventQueue.pop();
    auto it = listeners.find(static_cast<SDL_EventType>(event.type));
    if (it != listeners.end()) {
      for (const auto &listener : it->second) {
        listener(event);
      }
    }
  }
  return std::nullopt;
}

bool drakon::EventSystem::isEmpty() const { return eventQueue.empty(); }

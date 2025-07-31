#include <drakon/system/eventsystem.h>

drakon::EventSystem::EventSystem() {
  eventQueue = std::queue<drakon::event::Event>(); // Initialize the event queue
}

std::optional<drakon::Error>
drakon::EventSystem::enqueue(drakon::event::Event event) {
  try {
    eventQueue.push(event);
  } catch (const std::exception &e) {
    return Error(e.what());
  }
  return std::nullopt;
}

std::optional<drakon::Error>
drakon::EventSystem::addListener(const drakon::event::EventType type,
                                 drakon::EventSystem::Listener listener) {
  auto &vec = listeners[type];
  for (const auto &existing : vec) {
    if (existing.target_type() == listener.target_type() &&
        existing.target<void(drakon::event::Event &)>() ==
            listener.target<void(drakon::event::Event &)>()) {
      return Error("Listener already registered for this event type.");
    }
  }
  vec.push_back(listener);
  return std::nullopt;
}

bool drakon::EventSystem::removeListener(
    const drakon::event::EventType type,
    drakon::EventSystem::Listener listener) {
  auto it = listeners.find(type);
  if (it != listeners.end()) {
    auto &list = it->second;
    for (auto findIt = list.begin(); findIt != list.end(); ++findIt) {
      const auto &existing = *findIt;
      if (existing.target_type() == listener.target_type() &&
          existing.target<void(SDL_Event)>() ==
              listener.target<void(SDL_Event)>()) {
        list.erase(findIt);
        return true;
      }
    }
  }
  return false;
}

std::optional<drakon::Error> drakon::EventSystem::process() {
  // Process all events in the queue and notify listeners.
  while (!eventQueue.empty()) {
    auto event = eventQueue.front();
    eventQueue.pop();
    auto it = listeners.find(static_cast<drakon::event::EventType>(event.type));
    if (it != listeners.end()) {
      for (const auto &listener : it->second) {
        listener(event);
      }
    }
  }
  return std::nullopt;
}

bool drakon::EventSystem::isEmpty() const { return eventQueue.empty(); }

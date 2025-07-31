#include <drakon/_system/EventSystem.h>

drakon::system::EventSystem::EventSystem() {
  eventQueue = std::queue<drakon::event::Event>(); // Initialize the event queue
}

std::optional<drakon::error::Error>
drakon::system::EventSystem::enqueue(drakon::event::Event event) {
  try {
    eventQueue.push(event);
  } catch (const std::exception &e) {
    return drakon::error::Error(e.what());
  }
  return std::nullopt;
}

std::optional<drakon::error::Error> drakon::system::EventSystem::addListener(
    const drakon::event::EventType type,
    drakon::system::EventSystem::Listener listener) {
  auto &vec = listeners[type];
  for (const auto &existing : vec) {
    if (existing.target_type() == listener.target_type() &&
        existing.target<void(drakon::event::Event &)>() ==
            listener.target<void(drakon::event::Event &)>()) {
      return drakon::error::Error(
          "Listener already registered for this event type.");
    }
  }
  vec.push_back(listener);
  return std::nullopt;
}

bool drakon::system::EventSystem::removeListener(
    const drakon::event::EventType type,
    drakon::system::EventSystem::Listener listener) {
  auto it = listeners.find(type);
  if (it != listeners.end()) {
    auto &list = it->second;
    for (auto findIt = list.begin(); findIt != list.end(); ++findIt) {
      const auto &existing = *findIt;
      if (existing.target_type() == listener.target_type() &&
          existing.target<void(drakon::event::Event)>() ==
              listener.target<void(drakon::event::Event)>()) {
        list.erase(findIt);
        return true;
      }
    }
  }
  return false;
}

std::optional<drakon::error::Error> drakon::system::EventSystem::process() {
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

bool drakon::system::EventSystem::isEmpty() const { return eventQueue.empty(); }

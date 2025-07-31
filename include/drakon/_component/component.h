#pragma once

#include <atomic>
#include <memory>
#include <vector>

namespace drakon::component {

typedef unsigned long ComponentId;

struct Component {
  const ComponentId id;

  Component() : id(Component::getNextId()) {}

  virtual ~Component() = default;

  Component(const Component &) = default;
  Component(Component &&) = default;
  Component &operator=(const Component &) = default;
  Component &operator=(Component &&) = default;

  static ComponentId getNextId() { return nextId++; }

private:
  static std::atomic_uint nextId;
};
} // namespace drakon::component

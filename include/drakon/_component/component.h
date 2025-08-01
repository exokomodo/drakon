#pragma once

#include <atomic>
#include <memory>
#include <vector>

namespace drakon::component {

typedef unsigned long ComponentId;

ComponentId getNextComponentId();

struct Component {
  ComponentId id;

  Component() : id(getNextComponentId()) {}

  // Movable: default move constructor and move assignment
  Component(Component &&) = default;
  Component &operator=(Component &&) = default;

  // Prevent copying
  Component(const Component &) = default;
  Component &operator=(const Component &) = default;

  virtual ~Component() = default;
};
} // namespace drakon::component

#pragma once

#include <atomic>
#include <memory>
#include <vector>

namespace drakon::component {

typedef unsigned long ComponentId;

ComponentId getNextComponentId();

struct IComponent {
  ComponentId id;

  IComponent() : id(getNextComponentId()) {}

  // Movable: default move constructor and move assignment
  IComponent(IComponent &&) = default;
  IComponent &operator=(IComponent &&) = default;

  // Prevent copying
  IComponent(const IComponent &) = default;
  IComponent &operator=(const IComponent &) = default;

  virtual ~IComponent() = default;
};
} // namespace drakon::component

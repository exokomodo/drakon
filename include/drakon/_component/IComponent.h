#pragma once

namespace drakon::component {
struct IComponent {
  virtual void unload() {}

  virtual ~IComponent() = default;
};
} // namespace drakon::component
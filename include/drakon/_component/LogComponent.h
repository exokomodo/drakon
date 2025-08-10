#pragma once

#include <functional>
#include <optional>

#include <drakon/_component/IComponent.h>
#include <drakon/error>

namespace drakon::component {
struct LogComponent : public IComponent {
  LogComponent(std::string_view _message);
  LogComponent(std::string_view _message, bool _isOneShot);

  std::string_view message;
  const bool isOneShot = false;
  bool hasPrinted = false;
};
} // namespace drakon::component

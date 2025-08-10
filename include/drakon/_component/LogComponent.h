#pragma once

#include <drakon/_component/IComponent.h>
#include <drakon/error>
#include <string_view>

namespace drakon::component {
struct LogComponent : public IComponent {
  LogComponent(const std::string_view _message);
  LogComponent(const std::string_view _message, const bool _isOneShot);

  std::string_view message;
  const bool isOneShot = false;
  bool hasPrinted = false;
};
} // namespace drakon::component

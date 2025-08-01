#pragma once

#include <functional>

#include <drakon/_component/component.h>
#include <drakon/error>

namespace drakon::component {
struct PrintComponent : public Component {
  PrintComponent(std::string_view _message) : message(_message) {}

  std::optional<drakon::error::Error> process() {
    std::cout << "PrintComponent: " << message << std::endl;
    return std::nullopt;
  }

  std::string_view message;
};
} // namespace drakon::component

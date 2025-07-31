#pragma once

#include <drakon/error>
#include <optional>

namespace drakon::system {
struct ISystem {
  virtual ~ISystem() = default;
  virtual std::optional<drakon::error::Error> process() = 0;
};
} // namespace drakon::system

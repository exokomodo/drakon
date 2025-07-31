#pragma once

#include <drakon/error>
#include <optional>

namespace drakon {
struct Struct {
  Struct() {}

  std::optional<drakon::error::Error> someMethod() { return std::nullopt; }

private:
  Struct(const Struct &) = default;
  Struct(Struct &&) = default;
  Struct &operator=(const Struct &) = default;
  Struct &operator=(Struct &&) = default;

  ~Struct() {}
};
} // namespace drakon

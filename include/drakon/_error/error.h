#pragma once

#include <iostream>
#include <string_view>

namespace drakon::error {
struct Error {
  Error() = default;
  Error(const Error &) = default;
  Error(Error &&) = default;
  Error &operator=(const Error &) = default;
  Error &operator=(Error &&) = default;
  explicit Error(const std::string_view message);
  ~Error() = default;

  [[nodiscard]] std::string_view getMessage() const;

  friend std::ostream &operator<<(std::ostream &os, const Error &error) {
    return os << "Error: " << error.getMessage();
  }

protected:
  std::string_view message;
};
} // namespace drakon::error

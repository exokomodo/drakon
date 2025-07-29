#include <drakon/error.h>

drakon::Error::Error(const std::string_view _message) {
  if (_message.empty()) {
    throw std::invalid_argument("Error message cannot be empty");
  }
  message = _message;
}

[[nodiscard]] std::string_view drakon::Error::getMessage() const {
  return message;
}

std::ostream &operator<<(std::ostream &os, const drakon::Error &error) {
  return os << "Error: " << error.getMessage();
}

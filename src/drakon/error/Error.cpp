#include <drakon/error>

drakon::error::Error::Error(const std::string_view _message) {
  if (_message.empty()) {
    throw std::invalid_argument("Error message cannot be empty");
  }
  message = _message;
}

std::string_view drakon::error::Error::getMessage() const { return message; }

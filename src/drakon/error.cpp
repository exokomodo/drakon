#pragma once

#include <drakon/error.h>

drakon::Error::Error(const std::string_view message) {
  if (message.empty()) {
    throw std::invalid_argument("Error message cannot be empty");
  }
  this->message = message;
}

[[nodiscard]] std::string_view drakon::Error::getMessage() const {
  return message;
}

std::ostream &drakon::operator<<(std::ostream &os, const drakon::Error &error) {
  return os << "Error: " << error.getMessage();
}

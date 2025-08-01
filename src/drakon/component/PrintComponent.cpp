#include <drakon/component>

std::optional<drakon::error::Error>
drakon::component::PrintComponent::process() {
  std::cout << "PrintComponent: " << message << std::endl;
  return std::nullopt;
}
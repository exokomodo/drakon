#pragma once

#include <drakon/_component/IComponent.h>
#include <glm/vec3.hpp>

namespace drakon::component {
struct PositionComponent : public IComponent {
  PositionComponent(glm::vec3 _position) : position(_position) {}

  glm::vec3 position;
};
} // namespace drakon::component

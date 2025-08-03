#pragma once

#include <drakon/_component/component.h>
#include <glm/vec3.hpp>

namespace drakon::component {
struct PositionComponent : public Component {
  PositionComponent(glm::vec3 _position) : position(_position) {}

  glm::vec3 position;
};
} // namespace drakon::component

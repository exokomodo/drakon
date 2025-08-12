#pragma once

#include <drakon/_component/IComponent.h>
#include <glm/vec3.hpp>

namespace drakon::component {
struct PositionComponent : public IComponent {
  PositionComponent(const glm::vec3 _position);

  glm::vec3 position;
};
} // namespace drakon::component

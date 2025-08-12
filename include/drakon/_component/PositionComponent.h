#pragma once

#include <glm/vec3.hpp>

#include <drakon/_component/IComponent.h>

namespace drakon::component {
struct PositionComponent : public IComponent {
  PositionComponent();
  PositionComponent(const glm::vec3 _position);

  glm::vec3 position;
};
} // namespace drakon::component

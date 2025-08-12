#include <drakon/_component/PositionComponent.h>

drakon::component::PositionComponent::PositionComponent()
    : position(glm::vec3(0.0f, 0.0f, 0.0f)) {}

drakon::component::PositionComponent::PositionComponent(
    const glm::vec3 _position)
    : position(_position) {}

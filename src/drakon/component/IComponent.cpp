#include <drakon/_component/IComponent.h>

#include <atomic>

drakon::component::IComponent::IComponent() : id(getNextComponentId()) {}

static std::atomic_uint nextComponentId = 1;
drakon::component::ComponentId drakon::component::getNextComponentId() {
  return ++nextComponentId;
}

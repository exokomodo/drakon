#include <drakon/component>

static std::atomic_uint nextComponentId = 1;
drakon::component::ComponentId drakon::component::getNextComponentId() {
  return ++nextComponentId;
}

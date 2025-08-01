#include <drakon/component>

static std::atomic_uint nextId{0};
drakon::component::ComponentId drakon::component::getNextComponentId() {
  return ++nextId;
}

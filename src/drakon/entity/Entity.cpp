#include <drakon/_entity/Entity.h>

#include <atomic>

static std::atomic_uint nextEntityId = 1;
drakon::entity::Entity drakon::entity::getNextEntity() {
  return ++nextEntityId;
}

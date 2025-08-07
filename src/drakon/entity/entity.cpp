#include <drakon/_entity/entity.h>

static std::atomic_uint nextEntityId = 1;
drakon::entity::Entity drakon::entity::getNextEntity() {
  return ++nextEntityId;
}

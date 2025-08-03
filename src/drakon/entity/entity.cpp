#include <drakon/_entity/entity.h>

static std::atomic_uint nextId{0};
drakon::entity::Entity drakon::entity::getNextEntity() { return ++nextId; }

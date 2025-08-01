#include <drakon/entity>

static std::atomic_uint nextId{0};
drakon::entity::Entity drakon::entity::getNextEntity() { return ++nextId; }

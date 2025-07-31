#pragma once

#include <atomic>
#include <memory>
#include <vector>

namespace drakon::entity {

typedef unsigned long EntityId;

struct Entity {
  const EntityId id;

  Entity() : id(Entity::getNextId()) {}

  ~Entity() = default;

  Entity(const Entity &) = default;
  Entity(Entity &&) = default;
  Entity &operator=(const Entity &) = default;
  Entity &operator=(Entity &&) = default;

  static EntityId getNextId() { return nextId++; }

private:
  static std::atomic_uint nextId;
  std::vector<std::unique_ptr<void>> components;
};
} // namespace drakon::entity

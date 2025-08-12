#pragma once

#include <drakon/entity>
#include <drakon/error>
#include <expected>
#include <optional>
#include <typeinfo>
#include <unordered_map>
#include <vector>

namespace drakon::component {

struct IComponentCollection {
  virtual ~IComponentCollection() = default;
  virtual std::optional<drakon::error::Error>
  eraseAll(drakon::entity::Entity entity) = 0;
};

template <typename T> struct ComponentCollection : public IComponentCollection {
  std::optional<drakon::error::Error> insert(drakon::entity::Entity entity,
                                             T component) {
    if (entityToIndex.find(entity) != entityToIndex.end()) {
      return drakon::error::Error("Entity already has component");
    }

    components.push_back(component);
    entityToIndex[entity] = nextIndex;
    indexToEntity[nextIndex] = entity;
    nextIndex++;
    return std::nullopt;
  }

  std::optional<drakon::error::Error> erase(drakon::entity::Entity entity) {
    // Erase component from maps
    auto it = entityToIndex.find(entity);
    if (it == entityToIndex.end()) {
      return drakon::error::Error("Entity does not have component");
    }
    entityToIndex.erase(it);
    indexToEntity.erase(it->second);

    // Swap and pop to maintain density
    auto lastIndex = components.size() - 1;
    entityToIndex[indexToEntity[lastIndex]] = it->second;
    indexToEntity[it->second] = indexToEntity[lastIndex];
    components[it->second].unload(); // Call unload before removing
    components[it->second] = components[lastIndex];
    components.pop_back();
    nextIndex--;

    return std::nullopt;
  }

  bool has(drakon::entity::Entity entity) {
    auto it = entityToIndex.find(entity);
    return it != entityToIndex.end();
  }

  T &get(drakon::entity::Entity entity) {
    auto it = entityToIndex.find(entity);
    return components[it->second];
  }

  std::optional<drakon::error::Error>
  eraseAll(drakon::entity::Entity entity) override {
    return erase(entity);
  }

private:
  std::vector<T> components;
  std::unordered_map<drakon::entity::Entity, size_t> entityToIndex;
  std::unordered_map<size_t, drakon::entity::Entity> indexToEntity;
  size_t nextIndex = 0;
};
} // namespace drakon::component

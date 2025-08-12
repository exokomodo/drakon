#pragma once

#include <drakon/_component/ComponentCollection.h>
#include <drakon/_component/ComponentTypeId.h>
#include <drakon/entity>
#include <drakon/error>
#include <optional>
#include <stdint.h>
#include <typeindex>
#include <unordered_map>
#include <utility>
#include <vector>

namespace drakon::component {
struct ComponentManager {
  ComponentManager() {
    collections = std::unordered_map<
        std::type_index, std::pair<ComponentTypeId, IComponentCollection *>>();
    nextTypeId = 0;
  }
  ~ComponentManager() {
    for (auto &[_, pair] : collections) {
      delete pair.second; // Clean up component collections
    }
    collections.clear();
  }

  template <typename T> std::optional<drakon::error::Error> registerType() {
    const std::type_index &type = typeid(T);
    if (collections.find(type) != collections.end()) {
      return drakon::error::Error("Type already registered");
    }
    collections[type] =
        std::make_pair(nextTypeId++, new ComponentCollection<T>());
    return std::nullopt;
  }

  template <typename T> bool has(drakon::entity::Entity entity) {
    const auto collectionOpt = getCollectionByType<T>();
    if (!collectionOpt.has_value()) {
      return false; // Type not registered
    }
    const auto collection = *collectionOpt;
    return collection->has(entity);
  }

  template <typename T> T &get(drakon::entity::Entity entity) {
    const auto collectionOpt = getCollectionByType<T>();
    const auto collection = *collectionOpt;
    return collection->get(entity);
  }

  template <typename T>
  std::optional<drakon::error::Error> insert(drakon::entity::Entity entity,
                                             T component) {
    const auto collectionOpt = getCollectionByType<T>();
    if (!collectionOpt.has_value()) {
      return drakon::error::Error("Type not registered");
    }
    const auto collection = *collectionOpt;
    return collection->insert(entity, component);
  }

  template <typename T>
  std::optional<drakon::error::Error> erase(drakon::entity::Entity entity) {
    const auto collectionOpt = getCollectionByType<T>();
    if (!collectionOpt) {
      return drakon::error::Error("Type not registered");
    }
    const auto collection = *collectionOpt;
    return collection->remove(entity);
  }

  void eraseAll(drakon::entity::Entity entity) {
    for (auto &[type, pair] : collections) {
      auto collection = pair.second;
      collection->eraseAll(entity);
    }
  }

private:
  std::unordered_map<std::type_index,
                     std::pair<ComponentTypeId, IComponentCollection *>>
      collections;
  ComponentTypeId nextTypeId;

  template <typename T>
  std::optional<ComponentCollection<T> *> getCollectionByType() {
    const std::type_index &type = typeid(T);
    auto it = collections.find(type);
    if (it == collections.end()) {
      return std::nullopt;
    }
    return static_cast<ComponentCollection<T> *>(it->second.second);
  }
};
} // namespace drakon::component

#pragma once

#ifdef DRAKON_SDL
#include <SDL3/SDL.h>
#endif
#include <drakon/component>
#include <drakon/entity>
#include <drakon/error>
#include <drakon/system>
#include <expected>
#include <optional>
#include <unordered_map>
#include <vector>

namespace drakon::scene {
struct IScene {
  std::optional<drakon::error::Error> run();

  IScene(const Uint8 red, const Uint8 green, const Uint8 blue,
         const Uint8 alpha);

  IScene(const IScene &) = default;
  IScene(IScene &&) = default;
  IScene &operator=(const IScene &) = delete;
  IScene &operator=(IScene &&) = delete;

  virtual ~IScene();

  Uint8 red;
  Uint8 green;
  Uint8 blue;
  Uint8 alpha;

  virtual std::optional<drakon::error::Error> load() = 0;
  virtual std::optional<drakon::error::Error> unload();

  drakon::entity::Entity makeEntity();
  bool registerEntity(drakon::entity::Entity entity);

  std::vector<drakon::entity::Entity> getEntities() const;

  template <typename TComponent, typename... TArgs>
  std::expected<TComponent *, drakon::error::Error>
  addComponent(drakon::entity::Entity entity, TArgs &&...args) {
    static_assert(std::is_base_of_v<drakon::component::IComponent, TComponent>,
                  "TComponent must inherit from IComponent");
    if (std::find(entities.begin(), entities.end(), entity) == entities.end()) {
      return std::unexpected(drakon::error::Error("Entity does not exist"));
    }
    auto component = new TComponent(std::forward<TArgs>(args)...);
    const auto componentId = component->id;
    if constexpr (std::is_same_v<TComponent, drakon::component::LogComponent>) {
      if (entityComponentLogs.find(entity) == entityComponentLogs.end()) {
        entityComponentLogs.insert(
            {entity, std::vector<drakon::component::ComponentId>()});
      }
      entityComponentLogs.at(entity).push_back(componentId);
      componentLogs.insert({componentId, component});
    } else if constexpr (std::is_same_v<TComponent,
                                        drakon::component::PositionComponent>) {
      if (entityComponentPositions.find(entity) !=
          entityComponentPositions.end()) {
        return std::unexpected(
            drakon::error::Error("Entity already has a PositionComponent"));
      }
      entityComponentPositions.insert({entity, componentId});
      componentPositions.insert({componentId, component});
    } else if constexpr (std::is_same_v<TComponent,
                                        drakon::component::TextureComponent>) {
      if (entityComponentTextures.find(entity) ==
          entityComponentTextures.end()) {
        entityComponentTextures.insert(
            {entity, std::vector<drakon::component::ComponentId>()});
      }
      entityComponentTextures.at(entity).push_back(componentId);
      componentTextures.insert({componentId, component});
    } else {
      return std::unexpected(
          drakon::error::Error("Unsupported component type"));
    }
    return component;
  }

  template <typename TComponent>
  std::optional<std::vector<drakon::component::ComponentId>>
  getComponentIds(drakon::entity::Entity entity) {
    static_assert(std::is_base_of_v<drakon::component::IComponent, TComponent>,
                  "TComponent must inherit from IComponent");
    if (std::find(entities.begin(), entities.end(), entity) == entities.end()) {
      return std::nullopt;
    }
    if constexpr (std::is_same_v<TComponent, drakon::component::LogComponent>) {
      if (entityComponentLogs.find(entity) == entityComponentLogs.end()) {
        return std::nullopt;
      }
      return std::make_optional<std::vector<drakon::component::ComponentId>>(
          entityComponentLogs.at(entity));
    } else if constexpr (std::is_same_v<TComponent,
                                        drakon::component::PositionComponent>) {
      if (entityComponentPositions.find(entity) ==
          entityComponentPositions.end()) {
        return std::nullopt;
      }
      return std::make_optional<std::vector<drakon::component::ComponentId>>(
          std::vector<drakon::component::ComponentId>{
              entityComponentPositions[entity]});
    } else if constexpr (std::is_same_v<TComponent,
                                        drakon::component::TextureComponent>) {
      if (entityComponentTextures.find(entity) ==
          entityComponentTextures.end()) {
        return std::nullopt;
      }
      return std::make_optional<std::vector<drakon::component::ComponentId>>(
          entityComponentTextures.at(entity));
    } else {
      return std::nullopt;
    }
  }

  template <typename TComponent>
  std::optional<TComponent *>
  getComponent(drakon::component::ComponentId componentId) {
    static_assert(std::is_base_of_v<drakon::component::IComponent, TComponent>,
                  "TComponent must inherit from IComponent");
    if constexpr (std::is_same_v<TComponent, drakon::component::LogComponent>) {
      if (componentLogs.find(componentId) == componentLogs.end()) {
        return std::nullopt;
      }
      return std::make_optional(componentLogs[componentId]);
    } else if constexpr (std::is_same_v<TComponent,
                                        drakon::component::PositionComponent>) {
      if (componentPositions.find(componentId) == componentPositions.end()) {
        return std::nullopt;
      }
      return std::make_optional(componentPositions[componentId]);
    } else if constexpr (std::is_same_v<TComponent,
                                        drakon::component::TextureComponent>) {
      if (componentTextures.find(componentId) == componentTextures.end()) {
        return std::nullopt;
      }
      return std::make_optional(componentTextures[componentId]);
    } else {
      return std::nullopt; // Unsupported component type
    }
  }

private:
  std::vector<drakon::entity::Entity> entities;

  std::unordered_map<drakon::component::ComponentId,
                     drakon::component::PositionComponent *>
      componentPositions;
  std::unordered_map<drakon::component::ComponentId,
                     drakon::component::LogComponent *>
      componentLogs;
  std::unordered_map<drakon::component::ComponentId,
                     drakon::component::TextureComponent *>
      componentTextures;
  std::unordered_map<drakon::entity::Entity, drakon::component::ComponentId>
      entityComponentPositions;
  std::unordered_map<drakon::entity::Entity,
                     std::vector<drakon::component::ComponentId>>
      entityComponentLogs;
  std::unordered_map<drakon::entity::Entity,
                     std::vector<drakon::component::ComponentId>>
      entityComponentTextures;
};
} // namespace drakon::scene

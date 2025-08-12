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
  std::vector<drakon::entity::Entity> &getEntities();

  template <typename T>
  std::optional<drakon::error::Error>
  addComponent(drakon::entity::Entity entity, T component) {
    return componentManager.insert(entity, component);
  }

  template <typename T> bool hasComponent(drakon::entity::Entity entity) {
    return componentManager.has<T>(entity);
  }

  template <typename T> T &getComponent(drakon::entity::Entity entity) {
    return componentManager.get<T>(entity);
  }

private:
  std::vector<drakon::entity::Entity> entities;
  drakon::component::ComponentManager componentManager;
};
} // namespace drakon::scene

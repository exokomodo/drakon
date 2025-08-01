#pragma once

#ifdef DRAKON_SDL
#include <SDL3/SDL.h>
#endif
#include <drakon/component>
#include <drakon/entity>
#include <drakon/error>
#include <drakon/scene>
#include <drakon/system>
#include <list>
#include <memory>
#include <optional>
#include <vector>

namespace drakon::game {
struct Game {
  Game(const Game &) = default;
  Game &operator=(const Game &) = default;
  Game(Game &&) = default;
  Game &operator=(Game &&) = default;
  static Game *getInstance();

  std::optional<drakon::error::Error> run();

  std::optional<drakon::error::Error>
  setActiveScene(std::shared_ptr<drakon::scene::Scene> _activeScene);

  drakon::entity::Entity makeEntity();
  bool registerEntity(drakon::entity::Entity entity);

  // NOTE: Should be a friend of Entity
  template <typename TComponent, typename... TArgs>
  std::optional<drakon::error::Error>
  addComponent(drakon::entity::Entity entity, TArgs &&...args) {
    static_assert(std::is_base_of_v<drakon::component::Component, TComponent>,
                  "TComponent must inherit from Component");
    if (std::find(entities.begin(), entities.end(), entity) == entities.end()) {
      return drakon::error::Error("Entity does not exist");
    }
    auto component = TComponent(std::forward<TArgs>(args)...);
    if constexpr (std::is_same_v<TComponent,
                                 drakon::component::PrintComponent>) {
      if (entityComponentPrints.find(entity) == entityComponentPrints.end()) {
        entityComponentPrints.insert(
            {entity, std::vector<drakon::component::ComponentId>()});
      }
      entityComponentPrints.at(entity).push_back(component.id);
      componentPrints.insert({component.id, component});
    }
    return std::nullopt;
  }

  std::vector<std::shared_ptr<drakon::system::ISystem>> systems;

  Game(std::shared_ptr<drakon::scene::Scene> activeScene,
       const std::string_view title, int width, int height);
  ~Game();

  std::list<drakon::entity::Entity> entities;
  std::unordered_map<drakon::component::ComponentId,
                     drakon::component::PrintComponent>
      componentPrints;
  std::unordered_map<drakon::entity::Entity,
                     std::vector<drakon::component::ComponentId>>
      entityComponentPrints;

protected:
  std::shared_ptr<drakon::scene::Scene> activeScene;
  std::string_view title;
#ifdef DRAKON_SDL
  SDL_Window *window;
  SDL_Renderer *renderer;
#endif
  bool isRunning;

private:
  static Game *instance;
};
} // namespace drakon::game

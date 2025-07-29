#pragma once

#include <SDL3/SDL.h>
#include <drakon/error.h>
#include <drakon/scene.h>
#include <drakon/system/eventsystem.h>
#include <memory>
#include <optional>
#include <vector>

namespace drakon {
struct Game {
  Game(const Game &) = default;
  Game &operator=(const Game &) = default;
  Game(Game &&) = default;
  Game &operator=(Game &&) = default;
  static Game *getInstance();

  std::optional<Error> run();

  std::optional<Error> setActiveScene(std::shared_ptr<Scene> _activeScene) {
    if (activeScene) {
      activeScene->unload();
    }
    activeScene = _activeScene;
    activeScene->setEventSystem(eventSystem);
    return activeScene->load();
  }

protected:
  std::shared_ptr<Scene> activeScene;
  std::string_view title;
  SDL_Window *window;
  SDL_Renderer *renderer;
  bool isRunning;

  std::vector<std::shared_ptr<System>> systems;
  std::shared_ptr<EventSystem> eventSystem;

  Game(std::shared_ptr<Scene> activeScene, const std::string_view title,
       int width, int height);
  ~Game();

private:
  static Game *instance;
};
} // namespace drakon

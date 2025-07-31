#pragma once

#ifdef DRAKON_SDL
#include <SDL3/SDL.h>
#endif
#include <drakon/error>
#include <drakon/scene>
#include <drakon/system>
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
  setActiveScene(std::shared_ptr<drakon::scene::Scene> _activeScene) {
    if (activeScene) {
      activeScene->unload();
    }
    activeScene = _activeScene;
    return activeScene->load();
  }

protected:
  std::shared_ptr<drakon::scene::Scene> activeScene;
  std::string_view title;
#ifdef DRAKON_SDL
  SDL_Window *window;
  SDL_Renderer *renderer;
#endif
  bool isRunning;

  std::vector<std::shared_ptr<drakon::system::ISystem>> systems;

  Game(std::shared_ptr<drakon::scene::Scene> activeScene,
       const std::string_view title, int width, int height);
  ~Game();

private:
  static Game *instance;
};
} // namespace drakon::game

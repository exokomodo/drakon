#pragma once

#ifdef DRAKON_SDL
#include <SDL3/SDL.h>
#endif
#include <drakon/component>
#include <drakon/entity>
#include <drakon/error>
#include <drakon/scene>
#include <drakon/system>
#include <expected>
#include <memory>
#include <optional>
#include <string_view>
#include <vector>

namespace drakon::game {
struct Game {
  Game(const Game &) = default;
  Game &operator=(const Game &) = default;
  Game(Game &&) = default;
  Game &operator=(Game &&) = default;
  Game(std::string_view _title,
       std::shared_ptr<drakon::scene::Scene> _activeScene, int _width,
       int _height);
  ~Game();

  static Game *getInstance();

  std::optional<drakon::error::Error> run();

  std::shared_ptr<drakon::scene::Scene> getActiveScene();
  std::optional<drakon::error::Error>
  setActiveScene(std::shared_ptr<drakon::scene::Scene> _activeScene);

#ifdef DRAKON_SDL
  SDL_Window *getWindow() const;
  SDL_Renderer *getRenderer() const;
#endif

protected:
  bool isRunning;

private:
  static Game *instance;
  std::string_view title;
  std::shared_ptr<drakon::scene::Scene> activeScene;
  std::vector<std::shared_ptr<drakon::system::ISystem>> systems;
#ifdef DRAKON_SDL
  SDL_Window *window;
  SDL_Renderer *renderer;
#endif
};
} // namespace drakon::game

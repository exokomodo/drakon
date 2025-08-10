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
struct IGame {
  IGame(const IGame &) = default;
  IGame &operator=(const IGame &) = default;
  IGame(IGame &&) = default;
  IGame &operator=(IGame &&) = default;
  IGame(std::string_view _title,
       std::shared_ptr<drakon::scene::IScene> _activeScene, int _width,
       int _height);
  ~IGame();

  static IGame *getInstance();

  std::optional<drakon::error::Error> run();

  std::shared_ptr<drakon::scene::IScene> getActiveScene();
  std::optional<drakon::error::Error>
  setActiveScene(std::shared_ptr<drakon::scene::IScene> _activeScene);

#ifdef DRAKON_SDL
  SDL_Window *getWindow() const;
  SDL_Renderer *getRenderer() const;
#endif

protected:
  bool isRunning;

private:
  static IGame *instance;
  std::string_view title;
  std::shared_ptr<drakon::scene::IScene> activeScene;
  std::vector<std::shared_ptr<drakon::system::ISystem>> systems;
#ifdef DRAKON_SDL
  SDL_Window *window;
  SDL_Renderer *renderer;
#endif
};
} // namespace drakon::game

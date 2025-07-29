#pragma once

#include <SDL3/SDL.h>
#include <drakon/error.h>
#include <drakon/system/eventsystem.h>
#include <memory>
#include <optional>
#include <vector>

namespace drakon {
struct Game {
  std::optional<Error> run();

protected:
  std::string_view title;
  SDL_Window *window;
  SDL_Renderer *renderer;
  bool isRunning;

  std::vector<std::shared_ptr<System>> systems;
  std::shared_ptr<EventSystem> eventSystem;

  Game(const Game &) = default;
  Game(Game &&) = default;
  Game &operator=(const Game &) = delete;
  Game &operator=(Game &&) = delete;

  Game(const std::string_view title, int width, int height);
  ~Game();
};
} // namespace drakon

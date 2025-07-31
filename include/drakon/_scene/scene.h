#pragma once

#ifdef DRAKON_SDL
#include <SDL3/SDL.h>
#endif
#include <drakon/error>
#include <drakon/system>
#include <memory>
#include <optional>
#include <vector>

namespace drakon::scene {
struct Scene {
  std::optional<drakon::error::Error> run();

  Scene();
  Scene(const Uint8 red, const Uint8 green, const Uint8 blue,
        const Uint8 alpha);

  virtual ~Scene();

  Uint8 red;
  Uint8 green;
  Uint8 blue;
  Uint8 alpha;

  virtual std::optional<drakon::error::Error> load() = 0;
  virtual std::optional<drakon::error::Error> process() = 0;
  virtual std::optional<drakon::error::Error> unload() = 0;

  void
  setEventSystem(std::shared_ptr<drakon::system::EventSystem> _eventSystem) {
    eventSystem = _eventSystem;
  }

protected:
  std::shared_ptr<drakon::system::EventSystem> eventSystem;
  Scene(const Scene &) = default;
  Scene(Scene &&) = default;
  Scene &operator=(const Scene &) = delete;
  Scene &operator=(Scene &&) = delete;
};
} // namespace drakon::scene

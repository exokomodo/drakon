#pragma once

#ifdef DRAKON_SDL
#include <SDL3/SDL.h>
#endif
#include <drakon/error.h>
#include <drakon/system/eventsystem.h>
#include <memory>
#include <optional>
#include <vector>

namespace drakon {
struct Scene {
  std::optional<Error> run();

  Scene();
  Scene(const Uint8 red, const Uint8 green, const Uint8 blue,
        const Uint8 alpha);

  virtual ~Scene();

  Uint8 red;
  Uint8 green;
  Uint8 blue;
  Uint8 alpha;

  virtual std::optional<Error> load() = 0;
  virtual std::optional<Error> process() = 0;
  virtual std::optional<Error> unload() = 0;

  void setEventSystem(std::shared_ptr<drakon::EventSystem> _eventSystem) {
    eventSystem = _eventSystem;
  }

protected:
  std::shared_ptr<drakon::EventSystem> eventSystem;
  Scene(const Scene &) = default;
  Scene(Scene &&) = default;
  Scene &operator=(const Scene &) = delete;
  Scene &operator=(Scene &&) = delete;
};
} // namespace drakon

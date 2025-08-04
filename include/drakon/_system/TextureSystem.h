#pragma once

#ifdef DRAKON_SDL
#include <SDL3/SDL.h>
#endif
#include <drakon/_system/ISystem.h>
#include <drakon/error>
#include <drakon/event>
#include <functional>
#include <map>
#include <optional>
#include <queue>
#include <vector>

namespace drakon::system {
struct TextureSystem : public ISystem {
  TextureSystem() = default;
  TextureSystem(const TextureSystem &) = default;
  TextureSystem(TextureSystem &&) = default;
  TextureSystem &operator=(const TextureSystem &) = default;
  TextureSystem &operator=(TextureSystem &&) = default;
  ~TextureSystem() = default;

  std::optional<drakon::error::Error> process() override;
};
} // namespace drakon::system

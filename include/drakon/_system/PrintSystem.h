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
struct PrintSystem : public ISystem {
  PrintSystem() = default;
  PrintSystem(const PrintSystem &) = default;
  PrintSystem(PrintSystem &&) = default;
  PrintSystem &operator=(const PrintSystem &) = default;
  PrintSystem &operator=(PrintSystem &&) = default;
  ~PrintSystem() = default;

  std::optional<drakon::error::Error> process() override;
};
} // namespace drakon::system

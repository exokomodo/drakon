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
struct LogSystem : public ISystem {
  LogSystem() = default;
  LogSystem(const LogSystem &) = default;
  LogSystem(LogSystem &&) = default;
  LogSystem &operator=(const LogSystem &) = default;
  LogSystem &operator=(LogSystem &&) = default;
  ~LogSystem() = default;

  std::optional<drakon::error::Error> process() override;
};
} // namespace drakon::system

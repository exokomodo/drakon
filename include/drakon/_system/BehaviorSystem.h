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
struct BehaviorSystem : public ISystem {

  BehaviorSystem();
  BehaviorSystem(const BehaviorSystem &) = default;
  BehaviorSystem(BehaviorSystem &&) = default;
  BehaviorSystem &operator=(const BehaviorSystem &) = default;
  BehaviorSystem &operator=(BehaviorSystem &&) = default;
  ~BehaviorSystem() = default;

  std::optional<drakon::error::Error> process() override;
};
} // namespace drakon::system

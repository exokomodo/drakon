#pragma once

#include <functional>

#include <drakon/_component/component.h>
#include <drakon/error>

namespace drakon::component {
template <typename... TArgs> struct BehaviorComponent : public Component {
  BehaviorComponent(std::function<void(TArgs...)> behavior)
      : behavior(_behavior) {}

  std::optional<drakon::error::Error> proceed(TArgs... args) {
    return behavior(args...);
  }

private:
  std::function<std::optional<drakon::error::Error>(TArg...)> behavior;
};
} // namespace drakon::component

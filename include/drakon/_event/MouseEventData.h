#pragma once

#include <drakon/_event/IEventData.h>
#include <drakon/input>

namespace drakon::event {
struct MouseEventData : IEventData {
  drakon::input::InputType input;

  MouseEventData(drakon::input::InputType _input) : input(_input) {}
};
} // namespace drakon::event

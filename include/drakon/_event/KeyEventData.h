#pragma once

#include <drakon/_event/IEventData.h>
#include <drakon/input>

namespace drakon::event {
struct KeyEventData : IEventData {
  drakon::input::InputType input;

  KeyEventData(drakon::input::InputType _input) : input(_input) {}
};
} // namespace drakon::event

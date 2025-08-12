#pragma once

#include <drakon/_event/EventType.h>
#include <drakon/_event/IEventData.h>
#include <drakon/input>

namespace drakon::event {
struct KeyEventData : IEventData {
  drakon::input::InputType input;

  KeyEventData(drakon::input::InputType _input);
};
// Key events
static const EventType KeyUp = 0x6552B368;
static const EventType KeyDown = 0x46C6038E;
} // namespace drakon::event

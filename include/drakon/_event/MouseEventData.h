#pragma once

#include <drakon/_event/EventType.h>
#include <drakon/_event/IEventData.h>
#include <drakon/input>

namespace drakon::event {
struct MouseEventData : IEventData {
  drakon::input::InputType input;

  MouseEventData(drakon::input::InputType _input);
};
// Mouse events
static const EventType MouseClick = 0x270FB96E;
static const EventType MouseDoubleClick = 0x0D918A5B;
static const EventType MouseRightClick = 0x176F1014;
static const EventType MouseMove = 0x29F31CAE;
static const EventType MouseScrollUp = 0xD60370E3;
static const EventType MouseScrollDown = 0xF3454499;
} // namespace drakon::event

#pragma once

#include <drakon/_event/EventType.h>
#include <drakon/input>
#include <stdint.h>

namespace drakon::event {
#define DRAKON_KEY_EVENT_DATA_TYPE drakon::input::InputType

static const EventType KeyUp = 0x6552B368;
static const EventType KeyDown = 0x46C6038E;
} // namespace drakon::event

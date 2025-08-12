#pragma once

#include <stdint.h>

namespace drakon::event {
// NOTE: When making an event, generate a GUID and take the front bits
typedef uint32_t EventType;
static const EventType None = 0x00000000;
} // namespace drakon::event
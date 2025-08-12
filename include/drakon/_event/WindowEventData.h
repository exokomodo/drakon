#pragma once

#ifdef DRAKON_SDL
#include <SDL3/SDL.h>
#endif

#include <drakon/_event/EventType.h>
#include <drakon/_event/IEventData.h>

namespace drakon::event {
struct WindowEventData : IEventData {
#ifdef DRAKON_SDL
  SDL_Event sdl;
  WindowEventData(SDL_Event _sdl);
#endif
};
// Window events
static const EventType WindowResize = 0x778E2279;
static const EventType WindowClose = 0xDB2B2610;
} // namespace drakon::event

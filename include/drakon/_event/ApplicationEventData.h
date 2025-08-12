#pragma once

#ifdef DRAKON_SDL
#include <SDL3/SDL.h>
#endif

#include <drakon/_event/EventType.h>
#include <drakon/_event/IEventData.h>

namespace drakon::event {
struct ApplicationEventData : IEventData {
#ifdef DRAKON_SDL
  SDL_Event sdl;

  ApplicationEventData(SDL_Event _sdl);
#endif
};
// Application events
static const EventType Quit = 0xBFB0B536;
} // namespace drakon::event

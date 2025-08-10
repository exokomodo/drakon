#pragma once

#ifdef DRAKON_SDL
#include <SDL3/SDL.h>
#endif

#include <drakon/_event/IEventData.h>

namespace drakon::event {
struct WindowEventData : IEventData {
#ifdef DRAKON_SDL
  SDL_Event sdl;
  WindowEventData(SDL_Event _sdl) : sdl(_sdl) {}
#endif
};
} // namespace drakon::event

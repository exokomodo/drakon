#include <drakon/_event/WindowEventData.h>

#ifdef DRAKON_SDL
drakon::event::WindowEventData::WindowEventData(SDL_Event _sdl) : sdl(_sdl) {}
#endif

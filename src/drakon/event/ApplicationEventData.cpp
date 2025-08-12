#include <drakon/_event/ApplicationEventData.h>

#ifdef DRAKON_SDL
drakon::event::ApplicationEventData::ApplicationEventData(SDL_Event _sdl)
    : sdl(_sdl) {}
#endif

#pragma once

#ifdef DRAKON_SDL
#include <SDL3/SDL.h>
#endif
#include <string_view>

namespace drakon {
/**
 * @brief Starts a simple example app.
 */
int runSimple(std::string_view title);
} // namespace drakon

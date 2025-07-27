#ifndef DRAKON_H
#define DRAKON_H

#include <SDL3/SDL.h>
#include <string_view>

namespace drakon {
/**
 * @brief Starts the drakon application by displaying the splash message.
 */
int runSimple(std::string_view title);
} // namespace drakon

#endif // DRAKON_H

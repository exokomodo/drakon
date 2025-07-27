#ifndef DRAKON_H
#define DRAKON_H

#include <string_view>
#include <SDL3/SDL.h>

namespace drakon {
    /**
     * @brief Starts the drakon application by displaying the splash message.
     */
    int runSimple(std::string_view title);
}

#endif // DRAKON_H

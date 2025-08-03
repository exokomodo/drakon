#pragma once

// #ifdef DRAKON_SDL
#include <SDL3_image/SDL_image.h>
// #endif
#include <drakon/_component/PrintComponent.h>
#include <drakon/_component/component.h>
#include <glm/vec3.hpp>

namespace drakon::component {
struct TextureComponent : public Component {
  glm::vec3 position;
  TextureComponent(glm::vec3 _position, char *bmp_data, size_t bmp_len);
#ifdef DRAKON_SDL
  TextureComponent(glm::vec3 _position, SDL_Texture *_texture);
#endif

private:
  // #ifdef DRAKON_SDL
  char *image_data = nullptr;
  size_t image_len = 0;
  SDL_Texture *texture = NULL;
  // #endif
};
} // namespace drakon::component

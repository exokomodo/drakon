#pragma once

// #ifdef DRAKON_SDL
#include <SDL3_image/SDL_image.h>
// #endif
#include <drakon/_component/LogComponent.h>
#include <drakon/_component/IComponent.h>
#include <glm/vec3.hpp>

namespace drakon::component {
struct TextureComponent : public IComponent {
  glm::vec3 position;
  TextureComponent(glm::vec3 _position, unsigned char *bmp_data,
                   size_t bmp_len);
#ifdef DRAKON_SDL
  TextureComponent(glm::vec3 _position, SDL_Texture *_texture);

  SDL_Texture *getTexture() const;
#endif

private:
  // #ifdef DRAKON_SDL
  unsigned char *image_data = nullptr;
  size_t image_len = 0;
  SDL_Texture *texture = NULL;
  // #endif
};
} // namespace drakon::component

#pragma once

#ifdef DRAKON_SDL
#include <SDL3_image/SDL_image.h>
#endif
#include <drakon/_component/IComponent.h>
#include <glm/vec3.hpp>

namespace drakon::component {

typedef unsigned char *ImageData;

struct TextureComponent : public IComponent {
  glm::vec3 position;
  TextureComponent(const glm::vec3 _position, const ImageData bmp_data,
                   const size_t bmp_len);
  void unload() override;

#ifdef DRAKON_SDL
  TextureComponent(const glm::vec3 _position, SDL_Texture *_texture);

  SDL_Texture *getTexture() const;
#endif

private:
  ImageData image_data = nullptr;
  size_t image_len = 0;
#ifdef DRAKON_SDL
  SDL_Texture *texture = nullptr;
#endif
};
} // namespace drakon::component

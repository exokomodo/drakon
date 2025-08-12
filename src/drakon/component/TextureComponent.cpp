#include <drakon/_component/TextureComponent.h>
#include <drakon/game>

drakon::component::TextureComponent::TextureComponent(const glm::vec3 _position,
                                                      SDL_Texture *_texture)
    : position(_position), texture(_texture) {}

drakon::component::TextureComponent::TextureComponent(const glm::vec3 _position,
                                                      const ImageData bmp_data,
                                                      const size_t bmp_len)
    : position(_position) {
  const auto game = drakon::game::IGame::getInstance();
  image_data = bmp_data;
  image_len = bmp_len;

  texture = IMG_LoadTexture_IO(game->getRenderer(),
                               SDL_IOFromConstMem(bmp_data, bmp_len), true);
  if (!texture) {
    SDL_Log("Couldn't load icon: %s\n", SDL_GetError());
    throw std::runtime_error("Failed to load image texture");
  }
}

void drakon::component::TextureComponent::unload() {
  std::cout << "[TextureComponent] cleaning up" << std::endl;
#ifdef DRAKON_SDL
  if (texture) {
    SDL_DestroyTexture(texture);
    texture = nullptr;
  }
#endif
  image_data = nullptr;
  image_len = 0;
}

SDL_Texture *drakon::component::TextureComponent::getTexture() const {
  return texture;
}

#include <drakon/_component/TextureComponent.h>
#include <drakon/game>

drakon::component::TextureComponent::TextureComponent(glm::vec3 _position,
                                                      SDL_Texture *_texture)
    : position(_position), texture(_texture) {}
drakon::component::TextureComponent::TextureComponent(glm::vec3 _position,
                                                      unsigned char *bmp_data,
                                                      size_t bmp_len)
    : position(_position) {
  auto game = drakon::game::Game::getInstance();
  image_data = bmp_data;
  image_len = bmp_len;

  texture = IMG_LoadTexture_IO(game->getRenderer(),
                               SDL_IOFromConstMem(bmp_data, bmp_len), true);
  if (!texture) {
    SDL_Log("Couldn't load icon: %s\n", SDL_GetError());
    throw std::runtime_error("Failed to load image texture");
  }
}

SDL_Texture *drakon::component::TextureComponent::getTexture() const {
  return texture;
}

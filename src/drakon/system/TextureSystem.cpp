#include <drakon/_system/TextureSystem.h>
#include <drakon/game>

std::optional<drakon::error::Error> drakon::system::TextureSystem::process() {
  const auto game = drakon::game::IGame::getInstance();
  const auto scene = game->getActiveScene();
  for (const auto entity : scene->getEntities()) {
    if (!scene->hasComponent<drakon::component::TextureComponent>(entity)) {
      continue;
    }
    auto &textureComponent =
        scene->getComponent<drakon::component::TextureComponent>(entity);
#pragma region Get entity position
    glm::vec3 rootPosition = glm::vec3(0.0f, 0.0f, 0.0f);
    if (scene->hasComponent<drakon::component::PositionComponent>(entity)) {
      auto positionComponent =
          scene->getComponent<drakon::component::PositionComponent>(entity);
      rootPosition += positionComponent.position;
    }
#pragma endregion
    const auto position = rootPosition + textureComponent.position;
    const auto texture = textureComponent.getTexture();
    const auto dest =
        SDL_FRect{position.x, position.y, static_cast<float>(texture->w),
                  static_cast<float>(texture->h)};
    SDL_RenderTexture(game->getRenderer(), texture, nullptr, &dest);
  }
  return std::nullopt;
}

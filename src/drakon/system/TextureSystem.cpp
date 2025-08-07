#include <drakon/_system/TextureSystem.h>
#include <drakon/game>

std::optional<drakon::error::Error> drakon::system::TextureSystem::process() {
  const auto game = drakon::game::Game::getInstance();
  const auto scene = game->getActiveScene();
  for (const auto entity : scene->getEntities()) {
    auto textureComponentsOpt =
        scene->getComponentIds<drakon::component::TextureComponent>(entity);
    if (!textureComponentsOpt) {
      continue; // Skip entities without TextureComponent
    }

#pragma region Get entity position
    glm::vec3 rootPosition = glm::vec3(0.0f, 0.0f, 0.0f);
    auto positionComponentsOpt =
        scene->getComponentIds<drakon::component::PositionComponent>(entity);
    if (positionComponentsOpt) {
      const auto &positionComponents = *positionComponentsOpt;
      auto positionComponentOpt =
          scene->getComponent<drakon::component::PositionComponent>(
              positionComponents[0]);
      if (positionComponentOpt) {
        auto positionComponent = *positionComponentOpt;
        rootPosition += positionComponent->position;
      }
    }
#pragma endregion
    auto textureComponents = *textureComponentsOpt;
    for (const auto componentId : textureComponents) {
      auto textureComponentOpt =
          scene->getComponent<drakon::component::TextureComponent>(componentId);
      if (!textureComponentOpt) {
        continue; // Skip if component retrieval failed
      }
      const auto textureComponent = *textureComponentOpt;
      const auto position = rootPosition + textureComponent->position;
      const auto texture = textureComponent->getTexture();
      const auto dest =
          SDL_FRect{position.x, position.y, static_cast<float>(texture->w),
                    static_cast<float>(texture->h)};
      SDL_RenderTexture(game->getRenderer(), texture, nullptr, &dest);
    }
  }
  return std::nullopt;
}

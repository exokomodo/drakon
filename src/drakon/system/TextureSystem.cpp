#include <drakon/_system/TextureSystem.h>
#include <drakon/game>

std::optional<drakon::error::Error> drakon::system::TextureSystem::process() {
  const auto game = drakon::game::Game::getInstance();
  for (const auto entity : game->getEntities()) {
    auto textureComponentsOpt =
        game->getComponentIds<drakon::component::TextureComponent>(entity);
    if (!textureComponentsOpt) {
      continue; // Skip entities without TextureComponent
    }

#pragma region Get entity position
    glm::vec3 rootPosition = glm::vec3(0.0f, 0.0f, 0.0f);
    auto positionComponentsOpt =
        game->getComponentIds<drakon::component::PositionComponent>(entity);
    if (positionComponentsOpt) {
      const auto &positionComponents = *positionComponentsOpt;
      auto positionComponentOpt =
          game->getComponent<drakon::component::PositionComponent>(
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
          game->getComponent<drakon::component::TextureComponent>(componentId);
      if (!textureComponentOpt) {
        continue; // Skip if component retrieval failed
      }
      auto textureComponent = *textureComponentOpt;
      const auto position = rootPosition + textureComponent->position;
      std::cout << __BASE_FILE__ << ":" << __LINE__ << " "
                << "Entity: " << entity
                << ", Texture ID: " << textureComponent->id
                << ", Position: " << position.x << ", " << position.y << ", "
                << position.z << std::endl;
      const auto texture = textureComponent->getTexture();
      const auto dest =
          SDL_FRect{position.x, position.y, static_cast<float>(texture->w),
                    static_cast<float>(texture->h)};
      SDL_RenderTexture(game->getRenderer(), texture, nullptr, &dest);
    }
  }
  return std::nullopt;
}

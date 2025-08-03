#include <drakon/_system/TextureSystem.h>
#include <drakon/game>

std::optional<drakon::error::Error> drakon::system::TextureSystem::process() {
  const auto game = drakon::game::Game::getInstance();
  for (const auto entity : game->entities) {
    const auto it = game->entityComponentTextures.find(entity);
    if (it == game->entityComponentTextures.end()) {
      continue; // No TextureComponent for this entity
    }

#pragma region Get entity position
    glm::vec3 rootPosition = glm::vec3(0.0f, 0.0f, 0.0f);
    if (game->entityComponentPositions.contains(entity)) {
      const auto componentId = game->entityComponentPositions[entity];
      rootPosition +=
          game->componentPositions.find(componentId)->second.position;
    }
#pragma endregion
    const auto components = it->second;
    for (const auto componentId : components) {
      auto textureIt = game->componentTextures.find(componentId);
      if (textureIt != game->componentTextures.end()) {
        const auto textureComponent = textureIt->second;
        // Process the texture component, e.g., render it
        const auto position = rootPosition + textureComponent.position;
        std::cout << "Entity: " << entity
                  << ", Texture ID: " << textureComponent.id
                  << ", Position: " << position.x << ", " << position.y << ", "
                  << position.z << std::endl;
      } else {
        std::cerr << "Error: TextureComponent with ID " << componentId
                  << " not found." << std::endl;
      }
    }
  }
  return std::nullopt;
}

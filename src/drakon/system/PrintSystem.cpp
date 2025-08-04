#include <drakon/_system/PrintSystem.h>
#include <drakon/game>

std::optional<drakon::error::Error> drakon::system::PrintSystem::process() {
  auto game = drakon::game::Game::getInstance();
  for (const auto &entity : game->getEntities()) {
    auto components =
        game->getComponentIds<drakon::component::PrintComponent>(entity);
    if (!components) {
      continue; // Skip entities without PrintComponent
    }
    auto printComponents = *components;
    for (const auto &componentId : printComponents) {
      auto component =
          game->getComponent<drakon::component::PrintComponent>(componentId);
      if (!component) {
        continue; // Skip if component retrieval failed
      }
      const auto &printComponent = *component;
      std::cout << __BASE_FILE__ << ":" << __LINE__ << " "
                << "Entity: " << entity << ", Print ID: " << printComponent->id
                << ", Message: " << printComponent->message << std::endl;
    }
  }
  return std::nullopt;
}

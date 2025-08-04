#include <drakon/_system/PrintSystem.h>
#include <drakon/game>

std::optional<drakon::error::Error> drakon::system::PrintSystem::process() {
  auto game = drakon::game::Game::getInstance();
  for (const auto &entity : game->entities) {
    auto it = game->entityComponentPrints.find(entity);
    if (it != game->entityComponentPrints.end()) {
      const auto components = it->second;
      for (const auto &componentId : components) {
        auto printIt = game->componentPrints.find(componentId);
        if (printIt != game->componentPrints.end()) {
          const auto &printComponent = printIt->second;
          std::cout << __BASE_FILE__ << ":" << __LINE__ << " "
                    << "Entity: " << entity
                    << ", Print ID: " << printComponent->id
                    << ", Message: " << printComponent->message << std::endl;
        }
      }
    }
  }
  return std::nullopt;
}

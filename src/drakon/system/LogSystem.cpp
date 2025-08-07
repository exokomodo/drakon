#include <drakon/_system/LogSystem.h>
#include <drakon/game>

std::optional<drakon::error::Error> drakon::system::LogSystem::process() {
  auto game = drakon::game::Game::getInstance();
  auto scene = game->getActiveScene();
  for (const auto &entity : scene->getEntities()) {
    auto components =
        scene->getComponentIds<drakon::component::LogComponent>(entity);
    if (!components) {
      continue; // Skip entities without LogComponent
    }
    auto logComponents = *components;
    for (const auto &componentId : logComponents) {
      auto component =
          scene->getComponent<drakon::component::LogComponent>(componentId);
      if (!component) {
        continue; // Skip if component retrieval failed
      }
      const auto &logComponent = *component;
      if (logComponent->isOneShot && logComponent->hasPrinted) {
        continue; // Skip if it's a one-shot component that has already printed
      }
      std::cout << __BASE_FILE__ << ":" << __LINE__ << " "
                << "Entity: " << entity << ", Print ID: " << logComponent->id
                << ", Message: " << logComponent->message << std::endl;
      logComponent->hasPrinted = true;
    }
  }
  return std::nullopt;
}

#include <drakon/_system/LogSystem.h>
#include <drakon/game>

std::optional<drakon::error::Error> drakon::system::LogSystem::process() {
  auto game = drakon::game::IGame::getInstance();
  auto scene = game->getActiveScene();
  for (const auto &entity : scene->getEntities()) {
    if (!scene->hasComponent<drakon::component::LogComponent>(entity)) {
      continue; // Skip entities without LogComponent
    }
    auto &logComponent =
        scene->getComponent<drakon::component::LogComponent>(entity);
    if (logComponent.isOneShot && logComponent.hasPrinted) {
      continue; // Skip if it's a one-shot component that has already printed
    }
    std::cout << __BASE_FILE__ << ":" << __LINE__ << " " << "Entity: " << entity
              << ", Message: " << logComponent.message << std::endl;
    logComponent.hasPrinted = true;
  }
  return std::nullopt;
}

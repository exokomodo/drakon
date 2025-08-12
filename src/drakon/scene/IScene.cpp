#include <drakon/scene>

drakon::scene::IScene::IScene(const Uint8 _red, const Uint8 _green,
                              const Uint8 _blue, const Uint8 _alpha)
    : red(_red), green(_green), blue(_blue), alpha(_alpha) {
  entities = std::vector<drakon::entity::Entity>();
  componentManager = drakon::component::ComponentManager();
  // Register default component types
  componentManager.registerType<drakon::component::PositionComponent>();
  componentManager.registerType<drakon::component::LogComponent>();
  componentManager.registerType<drakon::component::TextureComponent>();
}

drakon::scene::IScene::~IScene() { unload(); }

drakon::entity::Entity drakon::scene::IScene::makeEntity() {
  auto entity = drakon::entity::Entity();
  entities.push_back(entity);
  return entity;
}

std::vector<drakon::entity::Entity> &drakon::scene::IScene::getEntities() {
  return entities;
}

std::optional<drakon::error::Error> drakon::scene::IScene::unload() {
  entities.clear();
  return std::nullopt;
}

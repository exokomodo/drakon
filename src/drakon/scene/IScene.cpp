#include <drakon/scene>

drakon::scene::IScene::IScene(const Uint8 _red, const Uint8 _green,
                              const Uint8 _blue, const Uint8 _alpha)
    : red(_red), green(_green), blue(_blue), alpha(_alpha) {
  entities = std::vector<drakon::entity::Entity>();
  componentLogs = std::unordered_map<drakon::component::ComponentId,
                                     drakon::component::LogComponent *>();
  entityComponentLogs =
      std::unordered_map<drakon::entity::Entity,
                         std::vector<drakon::component::ComponentId>>();
  componentPositions =
      std::unordered_map<drakon::component::ComponentId,
                         drakon::component::PositionComponent *>();
  entityComponentPositions =
      std::unordered_map<drakon::entity::Entity,
                         drakon::component::ComponentId>();
  componentTextures =
      std::unordered_map<drakon::component::ComponentId,
                         drakon::component::TextureComponent *>();
  entityComponentTextures =
      std::unordered_map<drakon::entity::Entity,
                         std::vector<drakon::component::ComponentId>>();
}

drakon::scene::IScene::~IScene() { unload(); }

drakon::entity::Entity drakon::scene::IScene::makeEntity() {
  auto entity = drakon::entity::Entity();
  registerEntity(entity);
  return entity;
}

bool drakon::scene::IScene::registerEntity(drakon::entity::Entity entity) {
  if (std::find(entities.begin(), entities.end(), entity) != entities.end()) {
    return false; // Entity already exists
  }
  entities.push_back(entity);
  return true;
}

std::vector<drakon::entity::Entity> drakon::scene::IScene::getEntities() const {
  return entities;
}

std::optional<drakon::error::Error> drakon::scene::IScene::unload() {
  entityComponentTextures.clear();
  entityComponentPositions.clear();
  entityComponentLogs.clear();
  for (auto &[_, component] : componentTextures) {
    delete component;
  }
  componentTextures.clear();
  for (auto &[_, component] : componentPositions) {
    delete component;
  }
  componentPositions.clear();
  for (auto &[_, component] : componentLogs) {
    delete component;
  }
  componentLogs.clear();
  entities.clear();
  return std::nullopt;
}
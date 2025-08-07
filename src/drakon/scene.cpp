#include <drakon/scene>

drakon::scene::Scene::Scene(const Uint8 _red, const Uint8 _green,
                            const Uint8 _blue, const Uint8 _alpha)
    : red(_red), green(_green), blue(_blue), alpha(_alpha) {
  entities = std::list<drakon::entity::Entity>();
  componentLogs =
      std::unordered_map<drakon::component::ComponentId,
                         std::shared_ptr<drakon::component::LogComponent>>();
  entityComponentLogs =
      std::unordered_map<drakon::entity::Entity,
                         std::vector<drakon::component::ComponentId>>();
  componentPositions = std::unordered_map<
      drakon::component::ComponentId,
      std::shared_ptr<drakon::component::PositionComponent>>();
  entityComponentPositions =
      std::unordered_map<drakon::entity::Entity,
                         drakon::component::ComponentId>();
  componentTextures = std::unordered_map<
      drakon::component::ComponentId,
      std::shared_ptr<drakon::component::TextureComponent>>();
  entityComponentTextures =
      std::unordered_map<drakon::entity::Entity,
                         std::vector<drakon::component::ComponentId>>();
}

drakon::scene::Scene::~Scene() {}

drakon::entity::Entity drakon::scene::Scene::makeEntity() {
  auto entity = drakon::entity::Entity();
  registerEntity(entity);
  return entity;
}

bool drakon::scene::Scene::registerEntity(drakon::entity::Entity entity) {
  if (std::find(entities.begin(), entities.end(), entity) != entities.end()) {
    return false; // Entity already exists
  }
  entities.push_back(entity);
  return true;
}

std::list<drakon::entity::Entity> drakon::scene::Scene::getEntities() const {
  return entities;
}
#pragma once

#include "OtherScene.h"
#include "smile_icon.h"
#include <drakon/entity>
#include <drakon/error>
#include <drakon/event>
#include <drakon/scene>
#include <optional>

struct HelloScene : public drakon::scene::IScene {
  HelloScene() : HelloScene(std::weak_ptr<drakon::scene::IScene>()) {}
  HelloScene(std::weak_ptr<drakon::scene::IScene> _nextScene)
      : IScene(0x00, 0x6C, 0x67, 0xFF), nextScene(_nextScene) {}

  std::weak_ptr<drakon::scene::IScene> nextScene;
  drakon::entity::Entity entity;
  std::weak_ptr<drakon::component::PositionComponent> position;
  std::weak_ptr<drakon::component::TextureComponent> texture;

  std::optional<drakon::error::Error> load() override {
    const auto eventSystem = drakon::system::EventSystem::getInstance();
    auto error =
        eventSystem->addListener(drakon::event::KeyDown, handleKeyDown);
    if (error) {
      return error;
    }
    const auto game = drakon::game::IGame::getInstance();
    entity = makeEntity();
    addComponent<drakon::component::LogComponent>(
        entity,
        std::string_view(
            "Hello DRAKON! Press arrow keys to change color, space to "
            "switch scene."),
        true);
    auto textureRes = addComponent<drakon::component::TextureComponent>(
        entity, glm::vec3{0.0f, 0.0f, 0.0f}, smile_icon_bmp,
        smile_icon_bmp_len);
    if (!textureRes) {
      return textureRes.error();
    }
    texture = *textureRes;
    auto positionRes = addComponent<drakon::component::PositionComponent>(
        entity, glm::vec3{0.0f, 0.0f, 0.0f});
    if (!positionRes) {
      return positionRes.error();
    }
    position = *positionRes;
    return std::nullopt;
  }

  ~HelloScene() {
    std::cout << "[HelloScene] cleaning up" << std::endl;
    nextScene.reset();
    position.reset();
    texture.reset();
    unload();
  }

  std::optional<drakon::error::Error> unload() override {
    const auto eventSystem = drakon::system::EventSystem::getInstance();
    if (!eventSystem->removeListener(drakon::event::KeyDown, handleKeyDown)) {
      return drakon::error::Error("Failed to remove key down listener");
    }
    // NOTE: If you do not want to clear all components and entities on unload,
    // you can leave this out.
    return drakon::scene::IScene::unload();
  }

private:
  MAKE_LISTENER(handleKeyDown) {
    if (event.type == drakon::event::KeyDown) {
      const auto input = event.asKey().lock()->input;
      const auto speed = 10.0f;
      switch (input) {
      case drakon::input::Left: {
        position.lock()->position += glm::vec3{-speed, 0.0f, 0.0f};
      } break;
      case drakon::input::Right: {
        position.lock()->position += glm::vec3{speed, 0.0f, 0.0f};
      } break;
      case drakon::input::Up: {
        texture.lock()->position += glm::vec3{0.0f, -speed, 0.0f};
      } break;
      case drakon::input::Down: {
        texture.lock()->position += glm::vec3{0.0f, speed, 0.0f};
      } break;
      case drakon::input::Space: {
        const auto _nextScene = nextScene.lock();
        if (!_nextScene) {
          break;
        }
        const auto game = drakon::game::IGame::getInstance();
        game->setActiveScene(_nextScene);
      } break;
      };
    }
  };
};

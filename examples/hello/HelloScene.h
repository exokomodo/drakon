#pragma once

#include "OtherScene.h"
#include "smile_icon.h"
#include <drakon/entity>
#include <drakon/error>
#include <drakon/event>
#include <drakon/scene>
#include <optional>

struct HelloScene : public drakon::scene::Scene {
  HelloScene() : HelloScene(nullptr) {}
  HelloScene(std::shared_ptr<drakon::scene::Scene> _nextScene)
      : Scene(0x00, 0x6C, 0x67, 0xFF), nextScene(_nextScene) {}

  std::shared_ptr<drakon::scene::Scene> nextScene;
  drakon::component::ComponentId positionId;
  drakon::component::ComponentId textureId;

  std::optional<drakon::error::Error> load() override {
    const auto eventSystem = drakon::system::EventSystem::getInstance();
    auto error = eventSystem->addListener(drakon::event::KeyDown, changeColor);
    if (error) {
      return error;
    }
    const auto game = drakon::game::Game::getInstance();
    const auto entity = game->makeEntity();
    game->addComponent<drakon::component::PrintComponent>(
        entity, std::string_view(
                    "Hello DRAKON! Press arrow keys to change color, space to "
                    "switch scene."));
    auto textureRes = game->addComponent<drakon::component::TextureComponent>(
        entity, glm::vec3{0.0f, 0.0f, 0.0f}, smile_icon_bmp,
        smile_icon_bmp_len);
    if (!textureRes) {
      return textureRes.error();
    }
    textureId = *textureRes;
    auto positionRes = game->addComponent<drakon::component::PositionComponent>(
        entity, glm::vec3{0.0f, 0.0f, 0.0f});
    if (!positionRes) {
      return positionRes.error();
    }
    positionId = *positionRes;
    return std::nullopt;
  }

  std::optional<drakon::error::Error> unload() override {
    const auto eventSystem = drakon::system::EventSystem::getInstance();
    if (!eventSystem->removeListener(drakon::event::KeyDown, changeColor)) {
      return drakon::error::Error("Failed to remove key down listener");
    }
    return std::nullopt;
  }

  std::optional<drakon::error::Error> process() override {
    return std::nullopt;
  }

private:
  MAKE_LISTENER(changeColor) {
    if (event.type == drakon::event::KeyDown) {
      const auto input = event.asKey()->input;
      auto game = drakon::game::Game::getInstance();
      const auto speed = 10.0f;
      switch (input) {
      case drakon::input::Left: {
        game->componentPositions[positionId]->position +=
            glm::vec3{-speed, 0.0f, 0.0f};
      } break;
      case drakon::input::Right: {
        game->componentPositions[positionId]->position +=
            glm::vec3{speed, 0.0f, 0.0f};
      } break;
      case drakon::input::Up: {
        game->componentTextures[textureId]->position +=
            glm::vec3{0.0f, -speed, 0.0f};
      } break;
      case drakon::input::Down: {
        game->componentTextures[textureId]->position +=
            glm::vec3{0.0f, speed, 0.0f};
      } break;
      case drakon::input::Space: {
        if (!nextScene) {
          break;
        }
        auto game = drakon::game::Game::getInstance();
        game->setActiveScene(nextScene);
      } break;
      };
    }
  };
};

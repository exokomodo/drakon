#pragma once

#include "OtherScene.h"
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
    // Process logic for HelloScene
    return std::nullopt;
  }

private:
  MAKE_LISTENER(changeColor) {
    if (event.type == drakon::event::KeyDown) {
      const auto input = event.asKey()->input;
      switch (input) {
      case drakon::input::Left: {
        red = std::max(0x00, red - 10);
      } break;
      case drakon::input::Right: {
        red = std::min(red + 10, 0xFF);
      } break;
      case drakon::input::Up: {
        green = std::max(0x00, green - 10);
      } break;
      case drakon::input::Down: {
        green = std::min(green + 10, 0xFF);
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

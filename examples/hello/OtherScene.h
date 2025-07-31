#pragma once

#include <drakon/error>
#include <drakon/scene>
#include <optional>

struct HelloScene;

struct OtherScene : public drakon::scene::Scene {
  OtherScene() : OtherScene(nullptr) {}
  OtherScene(std::shared_ptr<drakon::scene::Scene> _nextScene)
      : Scene(0xFF, 0x00, 0x00, 0xFF), nextScene(_nextScene) {}

  std::shared_ptr<drakon::scene::Scene> nextScene;

  std::optional<drakon::error::Error> load() override {
    if (!eventSystem->addListener(drakon::event::KeyDown, changeColor)) {
      return drakon::error::Error("Failed to add key down listener");
    }
    return std::nullopt;
  }

  std::optional<drakon::error::Error> unload() override {
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
        blue = std::max(0x00, blue - 10);
      } break;
      case drakon::input::Right: {
        blue = std::min(blue + 10, 0xFF);
      } break;
      case drakon::input::Up: {
        red = std::max(0x00, red - 10);
      } break;
      case drakon::input::Down: {
        red = std::min(red + 10, 0xFF);
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

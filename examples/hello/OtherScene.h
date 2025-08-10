#pragma once

#include <drakon/error>
#include <drakon/scene>
#include <optional>

struct HelloScene;

struct OtherScene : public drakon::scene::IScene {
  OtherScene() : OtherScene(nullptr) {}
  OtherScene(std::shared_ptr<drakon::scene::IScene> _nextScene)
      : IScene(0xFF, 0x00, 0x00, 0xFF), nextScene(_nextScene) {}

  std::shared_ptr<drakon::scene::IScene> nextScene;

  std::optional<drakon::error::Error> load() override {
    const auto eventSystem = drakon::system::EventSystem::getInstance();
    if (!eventSystem->addListener(drakon::event::KeyDown, handleKeyDown)) {
      return drakon::error::Error("Failed to add key down listener");
    }
    return std::nullopt;
  }

  std::optional<drakon::error::Error> unload() override {
    const auto eventSystem = drakon::system::EventSystem::getInstance();
    if (!eventSystem->removeListener(drakon::event::KeyDown, handleKeyDown)) {
      return drakon::error::Error("Failed to remove key down listener");
    }
    return drakon::scene::IScene::unload();
  }

private:
  MAKE_LISTENER(handleKeyDown) {
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
        auto game = drakon::game::IGame::getInstance();
        game->setActiveScene(nextScene);
      } break;
      };
    }
  };
};

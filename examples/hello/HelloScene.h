#pragma once

#include "OtherScene.h"
#include "drakon/error.h"
#include "drakon/scene.h"
#include <optional>

struct HelloScene : public drakon::Scene {
  HelloScene() : HelloScene(nullptr) {}
  HelloScene(std::shared_ptr<Scene> _nextScene)
      : Scene(0x00, 0x6C, 0x67, 0xFF), nextScene(_nextScene) {}

  std::shared_ptr<Scene> nextScene;

  std::optional<drakon::Error> load() override {
    if (!eventSystem->addListener(SDL_EVENT_KEY_DOWN, changeColor)) {
      return drakon::Error("Failed to add key down listener");
    }
    return std::nullopt;
  }

  std::optional<drakon::Error> unload() override {
    if (!eventSystem->removeListener(SDL_EVENT_KEY_DOWN, changeColor)) {
      return drakon::Error("Failed to remove key down listener");
    }
    return std::nullopt;
  }

  std::optional<drakon::Error> process() override {
    // Process logic for HelloScene
    return std::nullopt;
  }

private:
  MAKE_LISTENER(changeColor) {
    switch (event.key.key) {
    case SDLK_LEFT: {
      red = std::max(0x00, red - 10);
    } break;
    case SDLK_RIGHT: {
      red = std::min(red + 10, 0xFF);
    } break;
    case SDLK_UP: {
      green = std::max(0x00, green - 10);
    } break;
    case SDLK_DOWN: {
      green = std::min(green + 10, 0xFF);
    } break;
    case SDLK_SPACE: {
      if (!nextScene) {
        break;
      }
      auto game = drakon::Game::getInstance();
      game->setActiveScene(nextScene);
    } break;
    };
  };
};

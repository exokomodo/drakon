#include "HelloGame.h"
#include "HelloScene.h"
#include <drakon/error>
#include <drakon/scene>
#include <iostream>

int main() {
  // NOTE: This prevents some memory leaks but should not be used in production
  // code. https://wiki.libsdl.org/SDL3/SDL_HINT_SHUTDOWN_DBUS_ON_QUIT
  SDL_SetHint(SDL_HINT_SHUTDOWN_DBUS_ON_QUIT, "1");
  auto helloScene = std::make_shared<HelloScene>();
  auto otherScene = std::make_shared<OtherScene>(helloScene);
  helloScene->nextScene = otherScene;
  auto game = HelloGame("Hello DRAKON", helloScene, 640, 480);
  auto error = game.run();
  if (error) {
    std::cerr << *error << std::endl;
    return 1;
  }
  otherScene = nullptr;
  helloScene = nullptr;
  return 0;
}

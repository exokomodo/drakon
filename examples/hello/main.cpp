#include "HelloGame.h"
#include "HelloScene.h"
#include <drakon/error>
#include <drakon/scene>
#include <iostream>

int main() {
  auto helloScene = std::make_shared<HelloScene>();
  auto otherScene = std::make_shared<OtherScene>(helloScene);
  helloScene->nextScene = otherScene;
  auto game = HelloGame("Hello DRAKON", helloScene, 640, 480);
  auto error = game.run();
  if (error) {
    std::cerr << *error << std::endl;
    return 1;
  }
  return 0;
}

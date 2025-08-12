#include "HelloGame.h"
#include "HelloScene.h"
#include <drakon/error>
#include <drakon/scene>
#include <iostream>

int main() {
  auto helloScene = new HelloScene();
  auto otherScene = new OtherScene(helloScene);
  helloScene->nextScene = otherScene;
  auto game = HelloGame("Hello DRAKON", helloScene, 640, 480);
  auto error = game.run();
  if (error) {
    std::cerr << *error << std::endl;
    delete otherScene;
    otherScene = nullptr;
    delete helloScene;
    helloScene = nullptr;
    return 1;
  }
  delete otherScene;
  otherScene = nullptr;
  delete helloScene;
  helloScene = nullptr;
  return 0;
}

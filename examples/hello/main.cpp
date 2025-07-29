#include "HelloGame.h"
#include <iostream>

int main() {
  auto game = HelloGame("Hello DRAKON", 640, 480);
  auto error = game.run();
  if (error) {
    std::cerr << *error << std::endl;
    return 1;
  }
  return 0;
}

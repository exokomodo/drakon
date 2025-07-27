#include <drakon/game.h>
#include <string_view>

struct HelloGame : public drakon::Game {
  HelloGame(std::string_view title, int width, int height)
      : drakon::Game(title, width, height) {
    eventSystem->addListener(SDL_EVENT_QUIT,
                             [this](SDL_Event event) { quitHandler(event); });
  }

private:
  void quitHandler(SDL_Event event) { isRunning = false; }
};

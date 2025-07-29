#include <drakon/game.h>
#include <drakon/system/eventsystem.h>
#include <string_view>

struct HelloGame : public drakon::Game {
  HelloGame(std::shared_ptr<drakon::Scene> _activeScene,
            std::string_view _title, int _width, int _height)
      : drakon::Game(_activeScene, _title, _width, _height) {
    eventSystem->addListener(SDL_EVENT_QUIT, quit);
    eventSystem->addListener(SDL_EVENT_KEY_DOWN, handleKey);
  }

private:
  MAKE_LISTENER(handleKey) {
    if (event.key.key == SDLK_ESCAPE) {
      quit(event);
    }
  };
  MAKE_LISTENER(quit) { isRunning = false; };
};

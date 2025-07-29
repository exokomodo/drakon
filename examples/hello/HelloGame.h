#include <drakon/event.h>
#include <drakon/game.h>
#include <drakon/system/eventsystem.h>
#include <string_view>

struct HelloGame : public drakon::Game {
  HelloGame(std::shared_ptr<drakon::Scene> _activeScene,
            std::string_view _title, int _width, int _height)
      : drakon::Game(_activeScene, _title, _width, _height) {
    eventSystem->addListener(drakon::Quit, quit);
    eventSystem->addListener(drakon::KeyDown, handleKey);
  }

private:
  MAKE_LISTENER(handleKey) {
    const auto keyEvent = static_cast<drakon::KeyEvent &>(event);
    const auto code = keyEvent.getKeyCode();
    if (code == SDLK_ESCAPE) {
      quit(event);
    }
  };
  MAKE_LISTENER(quit) { isRunning = false; };
};

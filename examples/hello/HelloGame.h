#include <drakon/event.h>
#include <drakon/event/system.h>
#include <drakon/game.h>
#include <drakon/input.h>
#include <string_view>

struct HelloGame : public drakon::Game {
  HelloGame(std::shared_ptr<drakon::Scene> _activeScene,
            std::string_view _title, int _width, int _height)
      : drakon::Game(_activeScene, _title, _width, _height) {
    eventSystem->addListener(drakon::event::Quit, quit);
    eventSystem->addListener(drakon::event::KeyDown, handleKey);
  }

private:
  MAKE_LISTENER(handleKey) {
    const auto keyEvent = reinterpret_cast<drakon::event::KeyEvent &>(event);
    const auto code = keyEvent.getKeyCode();
    const auto escape = drakon::input::Escape;

    if (code == escape) {
      quit(event);
    }
  };
  MAKE_LISTENER(quit) { isRunning = false; };
};

#include <drakon/event.h>
#include <drakon/game.h>
#include <drakon/input.h>
// #include <drakon/system/eventsystem.h>
#include <string_view>

static const drakon::event::EventType customQuitType = 0x94FE6828;
struct CustomEventData : drakon::event::CustomEventData {
  std::string_view message;

  CustomEventData(std::string_view _message) : message(_message) {}
};

struct HelloGame : public drakon::Game {
  HelloGame(std::shared_ptr<drakon::Scene> _activeScene,
            std::string_view _title, int _width, int _height)
      : drakon::Game(_activeScene, _title, _width, _height) {
    eventSystem->addListener(drakon::event::Quit, quit);
    eventSystem->addListener(drakon::event::KeyDown, handleKey);
    eventSystem->addListener(customQuitType, customQuit);
  }

private:
  MAKE_LISTENER(handleKey) {
    if (event.type == drakon::event::KeyDown) {
      const auto input = event.asKey()->input;
      if (input == drakon::input::Escape) {
        eventSystem->enqueue(
            drakon::event::Event(customQuitType, CustomEventData("Goodbye!")));
      }
    }
  };
  MAKE_LISTENER(quit) { isRunning = false; };
  MAKE_LISTENER(customQuit) {
    std::cout << "Hello from " << event.asCustom<CustomEventData>()->message
              << std::endl;
    isRunning = false;
  };
};

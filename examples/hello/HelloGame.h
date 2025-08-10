#include <drakon/event>
#include <drakon/game>
#include <drakon/input>
#include <string_view>

static const drakon::event::EventType customQuitType = 0x94FE6828;
struct CustomEventData : drakon::event::CustomEventData {
  std::string_view message;

  CustomEventData(std::string_view _message) : message(_message) {}
};

struct HelloGame : public drakon::game::IGame {
  HelloGame(std::string_view _title,
            std::shared_ptr<drakon::scene::IScene> _activeScene, int _width,
            int _height)
      : drakon::game::IGame(_title, _activeScene, _width, _height) {
    const auto eventSystem = drakon::system::EventSystem::getInstance();
    eventSystem->addListener(drakon::event::Quit, quit);
    eventSystem->addListener(drakon::event::KeyDown, handleKey);
    eventSystem->addListener(customQuitType, customQuit);
  }

  ~HelloGame() {
    std::cout << "[HelloGame] cleaning up" << std::endl;
    const auto eventSystem = drakon::system::EventSystem::getInstance();
    eventSystem->removeListener(drakon::event::Quit, quit);
    eventSystem->removeListener(drakon::event::KeyDown, handleKey);
    eventSystem->removeListener(customQuitType, customQuit);
  }

private:
  MAKE_LISTENER(handleKey) {
    if (event.type == drakon::event::KeyDown) {
      const auto input = event.asKey()->input;
      if (input == drakon::input::Escape) {
        const auto eventSystem = drakon::system::EventSystem::getInstance();
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

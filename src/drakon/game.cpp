#include <drakon/game.h>

#define INIT_SYSTEM(member, type)                                              \
  (member) = std::make_shared<type>();                                         \
  systems.push_back(member);

drakon::Game::Game(const std::string_view _title, int _width, int _height)
    : title(_title), isRunning(false) {
  systems = std::vector<std::shared_ptr<drakon::System>>();
  INIT_SYSTEM(eventSystem, drakon::EventSystem);
  SDL_Init(SDL_INIT_VIDEO);
  SDL_CreateWindowAndRenderer(title.data(), _width, _height, 0, &window,
                              &renderer);
}

drakon::Game::~Game() {
  if (window) {
    SDL_DestroyWindow(window);
  }
  if (renderer) {
    SDL_DestroyRenderer(renderer);
  }
  renderer = nullptr;
  window = nullptr;
  SDL_Quit();
}

std::optional<drakon::Error> drakon::Game::run() {
  isRunning = true;
  SDL_Event event;
  while (isRunning) {
    // TODO: Consume events into an eventSystem, then dispatch them to the
    // game logic.
    while (SDL_PollEvent(&event)) {
      eventSystem->enqueue(event);
    }
    for (auto &system : systems) {
      auto error = system->process();
      if (error) {
        return error;
      }
    }
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 0x00, 0x6C, 0x67, 0xFF);
    SDL_RenderPresent(renderer);
  }

  return std::nullopt;
}

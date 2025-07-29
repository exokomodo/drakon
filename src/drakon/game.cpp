#include <drakon/game.h>

#define INIT_SYSTEM(member, type)                                              \
  (member) = std::make_shared<type>();                                         \
  systems.push_back(member);

drakon::Game::Game(std::shared_ptr<drakon::Scene> _activeScene,
                   std::string_view _title, int _width, int _height)
    : activeScene(_activeScene), title(_title), isRunning(false) {
  Game::instance = this;
  systems = std::vector<std::shared_ptr<drakon::System>>();
  INIT_SYSTEM(eventSystem, drakon::EventSystem);
  SDL_Init(SDL_INIT_VIDEO);
  SDL_CreateWindowAndRenderer(title.data(), _width, _height, 0, &window,
                              &renderer);
  activeScene->setEventSystem(this->eventSystem);
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
  SDL_Event sdlEvent;
  activeScene->load();
  while (isRunning) {
    while (SDL_PollEvent(&sdlEvent)) {
      const auto event = drakon::Event::fromSDL(sdlEvent);
      if (!event) {
        continue; // Skip unrecognized events
      }
      eventSystem->enqueue(*event);
    }
    for (auto &system : systems) {
      auto error = system->process();
      if (error) {
        return error;
      }
    }
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, activeScene->red, activeScene->green,
                           activeScene->blue, activeScene->alpha);
    SDL_RenderPresent(renderer);
  }

  return std::nullopt;
}

drakon::Game *drakon::Game::instance = nullptr;
drakon::Game *drakon::Game::getInstance() { return Game::instance; }

#include <drakon/event>
#include <drakon/game>

#define INIT_SYSTEM(type) systems.push_back(std::make_shared<type>());

drakon::game::Game::Game(std::shared_ptr<drakon::scene::Scene> _activeScene,
                         std::string_view _title, int _width, int _height)
    : activeScene(_activeScene), title(_title), isRunning(false) {
  Game::instance = this;
  // INIT_SYSTEM(drakon::system::BehaviorSystem);
#pragma region EventSystem
  systems = std::vector<std::shared_ptr<drakon::system::ISystem>>();
#ifdef DRAKON_SDL
  INIT_SYSTEM(drakon::system::EventSystem);
  SDL_Init(SDL_INIT_VIDEO);
  SDL_CreateWindowAndRenderer(title.data(), _width, _height, 0, &window,
                              &renderer);
#endif
#pragma endregion
}

drakon::game::Game::~Game() {
#ifdef DRAKON_SDL
  if (window) {
    SDL_DestroyWindow(window);
  }
  if (renderer) {
    SDL_DestroyRenderer(renderer);
  }
  renderer = nullptr;
  window = nullptr;
  SDL_Quit();
#endif
}

std::optional<drakon::error::Error> drakon::game::Game::run() {
  isRunning = true;
  activeScene->load();
#ifdef DRAKON_SDL
  SDL_Event sdlEvent;
  while (isRunning) {
    while (SDL_PollEvent(&sdlEvent)) {
      auto event = drakon::event::Event::fromSDL(sdlEvent);
#endif
      if (!event.isNone()) {
        auto error = drakon::system::EventSystem::getInstance()->enqueue(event);
        if (error) {
          return error;
        }
      }
    }
    for (auto &system : systems) {
      auto error = system->process();
      if (error) {
        return error;
      }
    }
#ifdef DRAKON_SDL
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, activeScene->red, activeScene->green,
                           activeScene->blue, activeScene->alpha);
    SDL_RenderPresent(renderer);
  }
#endif

  return std::nullopt;
}

drakon::game::Game *drakon::game::Game::instance = nullptr;
drakon::game::Game *drakon::game::Game::getInstance() { return Game::instance; }

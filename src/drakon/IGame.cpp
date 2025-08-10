#include <drakon/event>
#include <drakon/game>

#define INIT_SYSTEM(type) systems.push_back(std::make_shared<type>());

drakon::game::IGame::IGame(std::string_view _title,
                         std::shared_ptr<drakon::scene::IScene> _activeScene,
                         int _width, int _height)
    : isRunning(false), title(_title), activeScene(_activeScene) {
  IGame::instance = this;
  systems = std::vector<std::shared_ptr<drakon::system::ISystem>>();
  INIT_SYSTEM(drakon::system::LogSystem);
  INIT_SYSTEM(drakon::system::TextureSystem);
  INIT_SYSTEM(drakon::system::EventSystem);
#ifdef DRAKON_SDL
  SDL_Init(SDL_INIT_VIDEO);
  SDL_CreateWindowAndRenderer(title.data(), _width, _height, 0, &window,
                              &renderer);
#endif
}

drakon::game::IGame::~IGame() {
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

std::shared_ptr<drakon::scene::IScene> drakon::game::IGame::getActiveScene() {
  return activeScene;
}

std::optional<drakon::error::Error> drakon::game::IGame::setActiveScene(
    std::shared_ptr<drakon::scene::IScene> _activeScene) {
  if (activeScene) {
    activeScene->unload();
  }
  activeScene = _activeScene;
  return activeScene->load();
}

std::optional<drakon::error::Error> drakon::game::IGame::run() {
  assert(activeScene != nullptr &&
         "drakon::game::Game::activeScene was not specified");
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
#ifdef DRAKON_SDL
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, activeScene->red, activeScene->green,
                           activeScene->blue, activeScene->alpha);
#endif
    for (auto &system : systems) {
      auto error = system->process();
      if (error) {
        return error;
      }
    }
#ifdef DRAKON_SDL
    SDL_RenderPresent(renderer);
  }
#endif

  return std::nullopt;
}

drakon::game::IGame *drakon::game::IGame::instance = nullptr;
drakon::game::IGame *drakon::game::IGame::getInstance() { return IGame::instance; }
#ifdef DRAKON_SDL
SDL_Window *drakon::game::IGame::getWindow() const { return window; }
SDL_Renderer *drakon::game::IGame::getRenderer() const { return renderer; }
#endif

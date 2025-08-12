#include <drakon/event>
#include <drakon/game>

#define INIT_SYSTEM(systemType) systems.push_back(new systemType());

drakon::game::IGame::IGame(std::string_view _title,
                           drakon::scene::IScene *_activeScene, int _width,
                           int _height)
    : isRunning(false), title(_title), activeScene(_activeScene) {
  IGame::instance = this;
  systems = std::vector<drakon::system::ISystem *>();
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
  std::cout << "[IGame] cleaning up" << std::endl;
  activeScene = nullptr;
  IGame::instance = nullptr;
  for (auto &system : systems) {
    delete system;
  }
  systems.clear();
#ifdef DRAKON_SDL
  if (window) {
    SDL_DestroyWindow(window);
  }
  if (renderer) {
    SDL_DestroyRenderer(renderer);
  }
  renderer = nullptr;
  window = nullptr;
  SDL_QuitSubSystem(SDL_INIT_VIDEO);
  SDL_Quit();
#endif
}

drakon::scene::IScene *drakon::game::IGame::getActiveScene() {
  return activeScene;
}

std::optional<drakon::error::Error>
drakon::game::IGame::setActiveScene(drakon::scene::IScene *_activeScene) {
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
      const auto eventOpt = drakon::event::Event::fromSDL(sdlEvent);
#endif
      if (eventOpt) {
        auto error =
            drakon::system::EventSystem::getInstance()->enqueue(*eventOpt);
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
drakon::game::IGame *drakon::game::IGame::getInstance() {
  return IGame::instance;
}
#ifdef DRAKON_SDL
SDL_Window *drakon::game::IGame::getWindow() const { return window; }
SDL_Renderer *drakon::game::IGame::getRenderer() const { return renderer; }
#endif

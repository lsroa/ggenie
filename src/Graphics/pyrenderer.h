#include "Game/sdl_game.h"

class PyGame {
  public:
    std::shared_ptr<SDLGame> m_Game;
    PyGame() {
      m_Game = std::make_shared<SDLGame>();
      m_Game->Init();
    }

    void Run() {
      m_Game->Run();
    }

    Entity CreateEntity() {
      return m_Game->registry->CreateEntity();
    }
};

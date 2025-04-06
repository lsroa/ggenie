#pragma once

#include "Game/game.h"

class PyGame {
  public:
    std::shared_ptr<Game> m_Game;
    PyGame() {
      m_Game = std::make_shared<Game>();
      m_Game->Init();
    }

    void Run() {
      m_Game->Run();
    }

    Entity CreateEntity() {
      return m_Game->registry->CreateEntity();
    }
};

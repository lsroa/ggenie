#pragma once

#include "Game/game.h"
#include <functional>

class PyGame {
  public:
    std::shared_ptr<Game> m_Game;
    PyGame() {
      m_Game = std::make_shared<Game>();
      m_Game->Init();
    }

    void AssignUpdate(std::function<void(float)> func) {
      m_Game->update_func = func;
    }

    void Run() {
      m_Game->Run();
    }

    Entity CreateEntity() {
      return m_Game->registry->CreateEntity();
    }
};

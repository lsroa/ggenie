#pragma once

#include "../ECS/registry.h"
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>
#include <memory>

const int FPS = 60;
const int MPF = 1000 / FPS;

enum State { running, pause, quit };

class Game {
  private:
    SDL_Window *window;
    SDL_Renderer *renderer;
    State state;
    int ms = 0;
    std::shared_ptr<Registry> registry;

  public:
    Game();
    ~Game();
    void Destroy();
    void Init();
    void ProccessInput();
    void Render();
    void Setup();
    void Run();
    void Update();
    int width;
    int height;
};

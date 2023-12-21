#pragma once

#include "../src/AssetStore/asset_store.h"
#include "../src/ECS/ecs.h"
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
    int ms = 0;
    std::shared_ptr<Registry> registry;
    std::shared_ptr<Store> store;

  public:
    State state;
    Game();
    ~Game();
    void Destroy();
    void Init();
    void ProccessInput();
    void Render();
    void Setup();
    void LoadLevel(int level);
    void Run();
    void Update();
    int width;
    int height;
};

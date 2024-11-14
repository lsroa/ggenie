#include "Game/sdl_game.h"
#include "Graphics/renderer.h"

int main(int argc, char *argv[]) {
  if (argc > 1 && std::string(argv[1]) == "pikuma") {
    SDLGame game;
    game.Init();
    game.Run();
    game.Destroy();
  } else {
    Renderer renderer;
    renderer.Init();
    renderer.Run();
  }

  return 0;
}

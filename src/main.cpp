#include "Game/game.h"

#if __EMSCRIPTEN__
#include <emscripten.h>
#endif

void mainloop() {
  static Game game;
  if (game.state != State::running) {
    game.Init();
  }
  game.Run();
}

int main(int argc, char *argv[]) {

#if __EMSCRIPTEN__
  emscripten_set_main_loop(mainloop, 1, 0);
#else
  Game game;
  game.Init();
  game.Run();
  game.Destroy();
#endif

  return 0;
}

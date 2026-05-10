#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>

const Uint64 FPS = 144;
const Uint64 MILLISECONDS_PER_FRAME = 1000 / FPS;

class Game {
  private:
    bool isRunning;
    Uint64 millisecondsPreviousFrame;
    SDL_Window *window;
    SDL_Renderer *renderer;

  public:
    Game();
    ~Game();
    void Initialize();
    void Run();
    void Setup();
    void ProcessInput();
    void Update();
    void Render();
    void Destroy();

    int windowWidth;
    int windowHeight;

};

#endif

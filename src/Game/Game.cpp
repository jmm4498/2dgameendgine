#include "Game.h"
#include "../Logger/Logger.h"
#include "../ECS/ECS.h"
#include <SDL.h>
#include <SDL2/SDL_image.h>
#include <glm/glm.hpp>
#include <iostream>

Game::Game() {
  Logger::Init();
  isRunning = false;
  Logger::Log("Game constructor called");
}

Game::~Game() {
  Logger::Log("Game destructor called");
}

void Game::Initialize() {
  
  if(SDL_Init(SDL_INIT_EVERYTHING) != 0) {
    Logger::Err("Error initializing SDL. <ERR>: %s:", SDL_GetError());
    return;
  }

  SDL_DisplayMode displayMode;
  SDL_GetCurrentDisplayMode(0, &displayMode);

  windowWidth = 800;
  windowHeight = 600;

  window = SDL_CreateWindow(NULL, 
                            SDL_WINDOWPOS_CENTERED, 
                            SDL_WINDOWPOS_CENTERED,
                            windowWidth,
                            windowHeight,
                            SDL_WINDOW_BORDERLESS
                            );
  if(!window) {
    Logger::Err("Error creating SDL Window. <ERR>: %s:", SDL_GetError());
    return;
  }

  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

  if(!renderer) {
    Logger::Err("Error creating SDL Renderer. <ERR>: %s:", SDL_GetError());
    return;
  }

  SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);

  millisecondsPreviousFrame = SDL_GetTicks64();

  isRunning = true;

  return;
}

void Game::Setup() {
  //TODO:
  // Create entity  tank = registry.CreateEntity();
  
}

void Game::Update() {
  
  Uint64 timeToWait = MILLISECONDS_PER_FRAME - (SDL_GetTicks64() - millisecondsPreviousFrame);

  if(timeToWait > 0 && timeToWait <= MILLISECONDS_PER_FRAME) {
    SDL_Delay(timeToWait);
  }
  
  millisecondsPreviousFrame = SDL_GetTicks64();

}

void Game::Run() {
 
  Setup();

  while (isRunning) {
    ProcessInput();
    Update();
    Render();
  }
  
}

void Game::ProcessInput() {
  SDL_Event sdlEvent;
  while (SDL_PollEvent(&sdlEvent)) {
    switch(sdlEvent.type) {
      case SDL_QUIT:
        isRunning = false;
        break;
      case SDL_KEYDOWN:
        if (sdlEvent.key.keysym.sym == SDLK_ESCAPE) {
          isRunning = false;
        }
        break;
    }
  }
}

void Game::Render() {
  SDL_SetRenderDrawColor(renderer, 21, 21, 21, 255);
  SDL_RenderClear(renderer);

  SDL_RenderPresent(renderer);
}

void Game::Destroy() {
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
}

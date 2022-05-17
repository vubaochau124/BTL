#ifndef GAME_H
#define GAME_H

#include "GameBase.h"
#include "Snake.h"
#include "Texture.h"

class Game{
public:
  Game();
  ~Game();

  void HomeScreen();
  void RenderHomeScreen();
  void MainGame();
  void RenderMainGame();
  bool GameTick();

  void GenerateLevel();

  int GetScreen();

private:
  SDL_Window* window;
  SDL_Renderer* renderer;
  int screen;

  Button sPlay;
  
  Texture sHomeTex;
  Texture sPlayTex[BUTTON_TOTAL];
  Texture sBoardTex;

  SDL_Rect sHomeTexClip = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
  SDL_Rect sPlayTexClip = {300, 400, 250, 100};
  SDL_Rect sBoardTexClip = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};

  Snake sSnake;
};

#endif
#ifndef GAME_H
#define GAME_H

#include "GameBase.h"
#include "Texture.h"
#include "Button.h"
#include "Board.h"
#include "Snake.h"

class Game{
public:
  Game();
  ~Game();

  int GetScreen();

  void HomeScreen();
  void RenderHomeScreen();

  void GameScreen();
  void RenderGameScreen();

private:

  SDL_Window* gWindow;
  SDL_Renderer* gRenderer; 
  
  int screen;

  // homescreen
  Texture gHomeScreen;
  Texture gPlayButtonTex[BUTTON_TOTAL];
  Texture gBoardTex;
  
  SDL_Rect gHomeScreenClip = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
  SDL_Rect gPlayButtonClip  = {0, 0, BUTTON_WIDTH, BUTTON_HEIGHT};
  
  Button gPlayButton;

  // playscreen
  Board gBoard;
};

#endif
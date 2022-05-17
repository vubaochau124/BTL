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
  void ModeScreen();
  void RenderModeScreen();
  void MainGame();
  void RenderMainGame();
  void GameOver();
  void RenderGameOver();
  bool GameTick();

  void GenerateLevel();

  int GetScreen();

private:
  SDL_Window* window;
  SDL_Renderer* renderer;
  int screen;

  Button sPlay;
  Button sRetry;
  Button sBack;
  Button sClassic;
  Button sCampaign;
  
  Texture sHomeTex;
  Texture sPlayTex[BUTTON_TOTAL];
  Texture sBoardTex;
  Texture sModeTex;
  Texture sOverTex;
  Texture sRetryTex[BUTTON_TOTAL];
  Texture sClassicTex[BUTTON_TOTAL];
  Texture sCampaignTex[BUTTON_TOTAL];
  Texture sBackTex[BUTTON_TOTAL];

  SDL_Rect sHomeTexClip = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
  SDL_Rect sPlayTexClip = {300, 400, 250, 100};
  SDL_Rect sModeTexClip = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
  SDL_Rect sBoardTexClip = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
  SDL_Rect sOverTexClip = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
  SDL_Rect sRetryTexClip = {300, 400, 250, 100};
  SDL_Rect sBackTexClip = {300, 400, 250, 100};
  SDL_Rect sClassicTexClip = {300, 400, 250, 100};
  SDL_Rect sCampaignTexClip = {300, 400, 250, 100};

  Snake sSnake;
};

#endif
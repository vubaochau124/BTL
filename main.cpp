#include "GameBase.h"
#include "Texture.h"
#include "Button.h"
#include "Snake.h"
#include "Game.h"

Game game;

int main( int argc, char* args[] )
{
  bool GameRunning = true;
  
  SDL_Event e;

  while(GameRunning){
    if(game.GetScreen() == HOME_SCREEN)
      game.HomeScreen();
    else if(game.GetScreen() == GAME_SCREEN)
      game.GameScreen();
    else
      GameRunning = false;
  }
  
  IMG_Quit();
  SDL_Quit();

	return 0;
}


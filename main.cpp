#include "Button.h"
#include "Game.h"
#include "GameBase.h"
#include "Snake.h"
#include "Texture.h"

// *************************************************************************

Game sGame;

int main(int argc, char* argv[]) {
  bool isRunning = true;
  while(isRunning){
    if(sGame.GetScreen() == HOME)
      sGame.HomeScreen();
    else if(sGame.GetScreen() == MODE)
      sGame.ModeScreen();
    else if(sGame.GetScreen() == GAME)
      sGame.MainGame();
    else if(sGame.GetScreen() == OVER)
      sGame.GameOver();
    else
      isRunning = false;
  }

  return 0;
}
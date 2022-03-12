#include <SDL2/SDL.h>
#include <bits/stdc++.h>

using namespace std;

//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
SDL_Window* gWindow;
SDL_Renderer* gRenderer;

bool Init();
void Close();

int main( int argc, char* args[] )
{
	Init();
  SDL_Delay(3000);
  Close();
	return 0;
}

bool Init() {
  bool success = true;

  if (SDL_Init(SDL_INIT_VIDEO) < 0)
  {
    	cout << "SDL could not initialize. " <<  SDL_GetError() << '\n';
      success = false;
  }
  else {
      gWindow = SDL_CreateWindow("Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
      gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
      SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, 255);  
    }
  return success;
}

void Close()
{
  SDL_DestroyWindow(gWindow);
  gWindow = NULL;
  SDL_DestroyRenderer(gRenderer);
  gRenderer = NULL;
  SDL_Quit();
}
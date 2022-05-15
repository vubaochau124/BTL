#include "Game.h"

void Game::HomeScreen(){
  bool HomeScreenRunning = true;
  SDL_Event e;

  while(HomeScreenRunning){
    while(SDL_PollEvent(&e)){
      if(e.type == SDL_QUIT)
        screen = QUIT_SCREEN;
        HomeScreenRunning = false;

      if(e.type == SDL_MOUSEMOTION || e.type == SDL_MOUSEBUTTONDOWN){
        gPlayButton.HandleEvent(&e);
      }
    }

    if(gPlayButton.buttonSprite == BUTTON_DOWN){
      screen = GAME_SCREEN;
      HomeScreenRunning = false;
    }

    RenderHomeScreen();
  }
}

void Game::RenderHomeScreen(){
  SDL_RenderClear(gRenderer);
  gHomeScreen.Render(gRenderer, 0, 0, &gHomeScreenClip);
  gPlayButton.Render(gRenderer, gPlayButtonTex[gPlayButton.buttonSprite], &gPlayButtonClip);
  SDL_RenderPresent(gRenderer);
}

void Game::GameScreen(){
  bool GameRunning = true;
  int MoveTime = SDL_GetTicks();
  SDL_Event e;

  while(GameRunning){
    while(SDL_PollEvent(&e)){
      if(e.type == SDL_QUIT){
        GameRunning = false;
        screen = QUIT_SCREEN;
      }

      if(e.type == SDL_KEYDOWN){
        if(e.key.keysym.sym == SDLK_UP){
          gBoard.Move(UP);
          MoveTime = SDL_GetTicks() + ADDTIME;
        }
        if(e.key.keysym.sym == SDLK_DOWN){
          gBoard.Move(DOWN);
          MoveTime = SDL_GetTicks() + ADDTIME;
        }
        if(e.key.keysym.sym == SDLK_LEFT){
          gBoard.Move(LEFT);
          MoveTime = SDL_GetTicks() + ADDTIME;
        }
        if(e.key.keysym.sym == SDLK_RIGHT){
          gBoard.Move(RIGHT);
          MoveTime = SDL_GetTicks() + ADDTIME;
        }
      }
    }
    if (MoveTime < SDL_GetTicks()){
      MoveTime += ADDTIME;
      gBoard.ForceMove();
    }

    RenderGameScreen();
  }
}

void Game::RenderGameScreen(){
  SDL_RenderClear(gRenderer);

  gBoard.DrawBoard(gRenderer);

  SDL_RenderPresent(gRenderer);
}

int Game::GetScreen(){
  return screen;
}

Game::Game(){

  srand(time(0));

  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    cout << "SDL could not init video. " <<  SDL_GetError() << '\n';
  }
  else if (!IMG_Init(IMG_INIT_PNG)) {
    cout << "SDL could not init png. " <<  SDL_GetError() << '\n';
  }
  else {
    gWindow = SDL_CreateWindow("game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
    SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
    SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 128); 
  }

  screen = HOME_SCREEN;

  //home screen

  gHomeScreen.LoadTextureFromFile("images/screen.png", gRenderer);

  gPlayButtonTex[BUTTON_OUT].LoadTextureFromFile("images/play.png", gRenderer);
  gPlayButtonTex[BUTTON_OVER].LoadTextureFromFile("images/play_hovered.png", gRenderer);
  gPlayButtonTex[BUTTON_DOWN].LoadTextureFromFile("images/play_clicked.png", gRenderer);

  gPlayButton.Init(400,500,250,100);

  //play screen;

  gBoard.TextureInit(gRenderer);
}

Game::~Game(){
  SDL_DestroyWindow(gWindow);
  gWindow = NULL;
  SDL_DestroyRenderer(gRenderer);
  gRenderer = NULL;
  gHomeScreen.FreeTexture();
  SDL_Quit();
}

#include "Game.h"

void Game::HomeScreen(){
  SDL_Event e;

  for(auto isDone = false; !isDone; ){
    if(SDL_PollEvent(&e)){
      switch (e.type)
      {
      case SDL_QUIT:
        isDone = true;
        screen = ELSE;
        break;
      case SDL_MOUSEMOTION:
        sPlay.HandleEvent(&e);
        break;
      case SDL_MOUSEBUTTONDOWN:
        sPlay.HandleEvent(&e);
      default:
        break;
      }
    }

    if(sPlay.buttonSprite == BUTTON_DOWN){
      sPlay.buttonSprite = BUTTON_DEFAULT;
      screen = GAME;
      isDone = true;
    }

    RenderHomeScreen();
  }
}

void Game::RenderHomeScreen(){
  SDL_RenderClear(renderer);

  sHomeTex.Render(renderer, 0, 0, &sHomeTexClip);
  sPlay.Render(renderer, sPlayTex[sPlay.buttonSprite], &sPlayTexClip);

  SDL_RenderPresent(renderer);
}

void Game::MainGame(){
  sSnake.Reset();

  int tick = SDL_GetTicks();
  SDL_Event e;
  
  for(auto isDone = false; !isDone;){
    if(SDL_PollEvent(&e)){
      switch (e.type)
      {
      case SDL_QUIT:
        screen = ELSE;
        isDone = true;
        break;
      case SDL_KEYDOWN:
        switch (e.key.keysym.sym)
        {
        case SDLK_UP:
          sSnake.Move(UP);
          break;
        case SDLK_DOWN:
          sSnake.Move(DOWN);
          break;
        case SDLK_LEFT:
          sSnake.Move(LEFT);
          break;
        case SDLK_RIGHT:
          sSnake.Move(RIGHT);
          break;
        
        default:
          break;
        }
      default:
        break;
      }
    }

    // tick by tick movement
    int newTick = SDL_GetTicks();
    for(auto i = tick; i < newTick; i ++)
      if(!GameTick())
        isDone = true,
        screen = HOME;
    tick = newTick;
    
    RenderMainGame();
    
  }
}

void Game::RenderMainGame(){
  SDL_RenderClear(renderer);

  // draw the board later
  sBoardTex.Render(renderer, 0, 0, &sBoardTexClip);
  // draw the snake
  sSnake.Draw(renderer);
  
  SDL_RenderPresent(renderer);
}

bool Game::GameTick(){
  return sSnake.GameTick();
}

void Game::GenerateLevel(){

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
    window = SDL_CreateWindow("game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
    SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 128); 
  }

  screen = HOME;

  // Home
  sPlay.Init(350, 500, 250, 100);

  sHomeTex.LoadTextureFromFile("images/screen.png", renderer);
  sPlayTex[BUTTON_DEFAULT].LoadTextureFromFile("images/play.png", renderer);
  sPlayTex[BUTTON_HOVERED].LoadTextureFromFile("images/play_hovered.png", renderer);

  sSnake.Init(renderer);

  sBoardTex.LoadTextureFromFile("images/play_board.png", renderer);

}

Game::~Game(){
  // Home
  sHomeTex.FreeTexture();
  sPlayTex[BUTTON_DEFAULT].FreeTexture();
  sPlayTex[BUTTON_HOVERED].FreeTexture();

  SDL_DestroyWindow(window);
  SDL_DestroyRenderer(renderer);

  IMG_Quit();
  SDL_Quit();
}

int Game::GetScreen(){
  return screen;
}
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
      screen = MODE;
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

void Game::ModeScreen(){
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
        sClassic.HandleEvent(&e);
        sCampaign.HandleEvent(&e);
        break;
      case SDL_MOUSEBUTTONDOWN:
        sClassic.HandleEvent(&e);
        sCampaign.HandleEvent(&e);
        break;

      default:
        break;
      }
    }

    if(sClassic.buttonSprite == BUTTON_DOWN){
      sClassic.buttonSprite = BUTTON_DEFAULT;
      screen = CLASSIC;
      isDone = true;
    }
    if(sCampaign.buttonSprite == BUTTON_DOWN){
      sCampaign.buttonSprite = BUTTON_DEFAULT;
      screen = CAMPAIGN;
      isDone = true;
    }
  RenderModeScreen();
  }
}

void Game::RenderModeScreen(){
  SDL_RenderClear(renderer);

  sModeTex.Render(renderer, 0, 0, &sModeTexClip);
  sClassic.Render(renderer, sClassicTex[sClassic.buttonSprite], &sClassicTexClip);
  sCampaign.Render(renderer, sCampaignTex[sCampaign.buttonSprite], &sCampaignTexClip);

  SDL_RenderPresent(renderer);
}

void Game::ClassicGame(){
  sSnake.Reset(0); 

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
        screen = OVER;
    tick = newTick;
    
    RenderClassicGame();
    
  }
}

void Game::RenderClassicGame(){
  SDL_RenderClear(renderer);

  // draw the board later
  sBoardTex.Render(renderer, 0, 0, &sBoardTexClip);
  // draw the snake
  sSnake.Draw(renderer);
  
  SDL_RenderPresent(renderer);
}

void Game::CampaignGame(){
  int tick = SDL_GetTicks();
  SDL_Event e;
  int currentLevel = 1;
  sSnake.Reset(currentLevel);

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

    int newTick = SDL_GetTicks();
    for(auto i = tick; i < newTick; i ++)
      if(!GameTick())
        isDone = true,
        screen = OVER;
    tick = newTick;

    if(sSnake.IsFull()){
      if(currentLevel < 5)
        sSnake.Reset(++currentLevel);
      else 
        screen = OVER, // finish screen soon
        isDone = true;
    }

    RenderCampaignGame();
  }
}

void Game::RenderCampaignGame(){
  SDL_RenderClear(renderer);

  sBoardTex.Render(renderer, 0, 0, &sBoardTexClip);
  sSnake.Draw(renderer);
  sSnake.ProgressBar(renderer);

  SDL_RenderPresent(renderer);
}

void Game::GameOver(){
  SDL_Event e;

  for (auto isDone = false; !isDone;){
    if(SDL_PollEvent(&e)){
      switch (e.type)
      {
      case SDL_QUIT:
        isDone = true;
        screen = ELSE;
        break;
      case SDL_MOUSEMOTION:
        sRetry.HandleEvent(&e);
        sBack.HandleEvent(&e);
        break;
      case SDL_MOUSEBUTTONDOWN:
        sRetry.HandleEvent(&e);
        sBack.HandleEvent(&e);
      default:
        break;
      }

      if(sRetry.buttonSprite == BUTTON_DOWN){
        sRetry.buttonSprite = BUTTON_DEFAULT;
        if(sSnake.GetLevel())
          screen = CAMPAIGN;
        else
          screen = CLASSIC;
        isDone = true;
      }
      if(sBack.buttonSprite == BUTTON_DOWN){
        sBack.buttonSprite = BUTTON_DEFAULT;
        screen = HOME;
        isDone = true;
      }
      
    }
    RenderGameOver();
  }
}

void Game::RenderGameOver(){
  SDL_RenderClear(renderer);

  sOverTex.Render(renderer, 0, 0, &sOverTexClip);
  sRetry.Render(renderer, sRetryTex[sRetry.buttonSprite], &sRetryTexClip);
  sBack.Render(renderer, sBackTex[sBack.buttonSprite], &sBackTexClip);

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

  // Mode

  sClassic.Init(350, 350, 250, 100);
  sCampaign.Init(350, 500, 250, 100);

  sModeTex.LoadTextureFromFile("images/mode_screen.png", renderer);
  sClassicTex[BUTTON_DEFAULT].LoadTextureFromFile("images/classic.png", renderer);
  sClassicTex[BUTTON_HOVERED].LoadTextureFromFile("images/classic_hovered.png", renderer);
  sCampaignTex[BUTTON_DEFAULT].LoadTextureFromFile("images/campaign.png", renderer);
  sCampaignTex[BUTTON_HOVERED].LoadTextureFromFile("images/campaign_hovered.png", renderer);
  
  // Game
  sSnake.Init(renderer);

  sBoardTex.LoadTextureFromFile("images/play_board.png", renderer);

  // Game Over 
  sRetry.Init(350, 370, 250, 100);
  sBack.Init(350, 500, 250, 100);

  sOverTex.LoadTextureFromFile("images/game_over.png", renderer);
  sRetryTex[BUTTON_DEFAULT].LoadTextureFromFile("images/retry_button.png", renderer);
  sRetryTex[BUTTON_HOVERED].LoadTextureFromFile("images/retry_button_hovered.png", renderer);
  sBackTex[BUTTON_DEFAULT].LoadTextureFromFile("images/quit_button.png", renderer);
  sBackTex[BUTTON_HOVERED].LoadTextureFromFile("images/quit_button_hovered.png", renderer);
}

Game::~Game(){
  // Home
  sHomeTex.FreeTexture();
  sOverTex.FreeTexture();
  sModeTex.FreeTexture();
  sPlayTex[BUTTON_DEFAULT].FreeTexture();
  sPlayTex[BUTTON_HOVERED].FreeTexture();
  sRetryTex[BUTTON_DEFAULT].FreeTexture();
  sRetryTex[BUTTON_HOVERED].FreeTexture();
  sClassicTex[BUTTON_DEFAULT].FreeTexture();
  sClassicTex[BUTTON_HOVERED].FreeTexture();
  sCampaignTex[BUTTON_DEFAULT].FreeTexture();
  sCampaignTex[BUTTON_HOVERED].FreeTexture();
  sBackTex[BUTTON_DEFAULT].FreeTexture();
  sBackTex[BUTTON_HOVERED].FreeTexture();
  
  SDL_DestroyWindow(window);
  SDL_DestroyRenderer(renderer);

  IMG_Quit();
  SDL_Quit();
}

int Game::GetScreen(){
  return screen;
}
#include "Snake.h"

Snake::Snake(){
  
}

Snake::~Snake(){
  head.FreeTexture();
  body.FreeTexture();
  tail.FreeTexture();
  bodyTurn.FreeTexture();
  headOpen.FreeTexture();
}

void Snake::Init(SDL_Renderer* renderer){
  // length
  length = 3;

  for (int i=0; i< length; i++){
    currentSnake[i].first = 4-i;
    currentSnake[i].second = 2;
  }
  // direction
  direction = RIGHT;

  // image
  head.LoadTextureFromFile("images/head.png", renderer);
  body.LoadTextureFromFile("images/body.png", renderer);
  tail.LoadTextureFromFile("images/tail.png", renderer);
  bodyTurn.LoadTextureFromFile("images/body_turn", renderer);
  headOpen.LoadTextureFromFile("images/head_open", renderer);
}

void Snake::Draw(SDL_Renderer* renderer){
  for(int i = 0; i < length; i ++){
    if(i == 0){
      // head
      // head.Render(x, y)
      head.Render(renderer, BOARD_X + currentSnake[i].first*32, 
                  BOARD_Y + currentSnake[i].second*32, &headclip);
    }
    else if(i == length - 1){
      // tail
      tail.Render(renderer, BOARD_X + currentSnake[i].first*32, 
                  BOARD_Y + currentSnake[i].second*32, &headclip);
    }
    else{
      // body 
      body.Render(renderer, BOARD_X + currentSnake[i].first*32, 
                  BOARD_Y + currentSnake[i].second*32, &headclip);
    }
  }
}

void Snake::Move(int moveType){
  // neu dang co direction doi lap thi khong move
  if(moveType == UP){
    lastTail = currentSnake[length - 1];
    for(int i = length - 1; i > 0; i --)
      currentSnake[i] = currentSnake[i - 1];
    currentSnake[0].second --;
    direction = UP;
  }
  if(moveType == DOWN){
    lastTail = currentSnake[length - 1];
    for(int i = length - 1; i > 0; i --)
      currentSnake[i] = currentSnake[i - 1];
    currentSnake[0].second ++;
    direction = DOWN;
  }
  if(moveType == LEFT){
    lastTail = currentSnake[length - 1];
    for(int i = length - 1; i > 0; i --)
      currentSnake[i] = currentSnake[i - 1];
    currentSnake[0].first --;
    direction = LEFT;
  } 
  if(moveType == RIGHT){
    lastTail = currentSnake[length - 1];
    for(int i = length - 1; i > 0; i --)
      currentSnake[i] = currentSnake[i - 1];
    currentSnake[0].first ++;
    direction = RIGHT;
  }
}

void Snake::ForceMove(){
  lastTail = currentSnake[length - 1];
  for (int i = length - 1; i > 0; i --){
    currentSnake[i] = currentSnake[i - 1];
  }
  if (direction == UP)
    currentSnake[0].second --;
  if (direction == DOWN)
    currentSnake[0].second ++;
  if (direction == LEFT)
    currentSnake[0].first --;
  if (direction == RIGHT)
    currentSnake[0].first ++;
  currentSnake[0].first = (currentSnake[0].first + BOARD_WIDTH) % BOARD_WIDTH; 
  currentSnake[0].second = (currentSnake[0].second + BOARD_HEIGHT) % BOARD_HEIGHT;
}

bool Snake::checkMove(){
  // check currentSnake[0]
  for (int i = 1; i < length; i++)
    if (currentSnake[0] == currentSnake[i])
      return false;
    
  return true;
}

void Snake::Growth(){
  length ++;
  currentSnake[length - 1] = lastTail;
}

pair<int, int> Snake::GetHeadPos(){
  return currentSnake[0];
}

pair<int, int> Snake::GetTailPos(){
  return lastTail;
}

int Snake::GetDirection(){
  return direction;
}
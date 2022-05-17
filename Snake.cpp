#include "Snake.h"

Snake::Snake(){
  snakeQueue.push_back(make_pair(5, 7));
  snakeQueue.push_back(make_pair(5, 6));
  snakeQueue.push_back(make_pair(5, 5));

  FoodGen();
}

Snake::~Snake(){
  // Game
  sHead.FreeTexture();
  sBody.FreeTexture();
  sBodyTurn.FreeTexture();
  sTail.FreeTexture();
  sFood.FreeTexture();
}

void Snake::Move(int moveType){
  switch (moveType)
  {
  case UP:
    if(dx != 0 || dy != 1)
      dx = 0,
      dy = -1,
      MOVE_TIME = 100;
    break;
  case DOWN:
    if(dx != 0 || dy != -1)
      dx = 0,
      dy = 1,
      MOVE_TIME = 100;
    break;
  case LEFT:
    if(dx != 1 || dy != 0)
      dx = -1,
      dy = 0,
      MOVE_TIME = 100;
    break;
  case RIGHT:
    if(dx != -1 || dy != 0)
      dx = 1,
      dy = 0,
      MOVE_TIME = 100;
    break;
  default:
    MOVE_TIME = 200;
    break;
  }
}

bool Snake::GameTick(){
  if(gameTick++ % MOVE_TIME == 0){
    // execute the move
    pair<int, int> head = snakeQueue.front();
    head.first += dx;
    head.second += dy;
    
    // hit the snake body
    for(auto &it: snakeQueue)
      if(it == head){
        return false;
      }
    
    // if hit the board border, appear on the other side of the board
    if(head.first < 0 || head.first >= BOARD_WIDTH || 
       head.second < 0 || head.second >= BOARD_HEIGHT){
      head.first = (head.first + BOARD_WIDTH) % BOARD_WIDTH;
      head.second = (head.second + BOARD_HEIGHT) % BOARD_HEIGHT;
    }

    // push the new move in
    snakeQueue.push_front(head);
    // not hit the food
    if(head.first != foodX || head.second != foodY)
      snakeQueue.pop_back();
    else
      FoodGen();
  }
  return true;
}

void Snake::FoodGen(){
  for(auto rng = true; rng; ){
    foodX = rand() % BOARD_WIDTH;
    foodY = rand() % BOARD_HEIGHT;

    rng = false;
    for(auto it = snakeQueue.begin(); it != snakeQueue.end(); it ++){
      if(it->first == foodX && it->second == foodY){
        rng = true;
        break;
      }
    }
  }
}

void Snake::Draw(SDL_Renderer* renderer){
  SDL_Rect dst = {0, 0, 32, 32};
  int deltaS[][3] = {
    {-1, 0, 0}, 
    {0, -1, 90}, 
    {1, 0, 180}, 
    {0, 1, 270}
  };

  for(auto it = snakeQueue.begin(); it != snakeQueue.end(); it ++){
    auto &curPart = *it;
    double angle = 0;
    if(it == snakeQueue.begin()){
      // draw the head

      auto &nextPart = *(it + 1);
      for(int i = 0; i < 4; i ++){
        if((curPart.first + deltaS[i][0] + BOARD_WIDTH) % BOARD_WIDTH == nextPart.first 
        && (curPart.second + deltaS[i][1] + BOARD_HEIGHT) % BOARD_HEIGHT == nextPart.second){
          angle = deltaS[i][2];
          break;
        }
      }
      dst.x = 32 * curPart.first;
      dst.y = 32 * curPart.second;
      
      sHead.RenderEx(renderer, &dst, angle);
    }
    else if(it + 1 == snakeQueue.end()){
      // draw the tail

      auto &prevPart = *(it - 1);
      for(int i = 0; i < 4; i ++){
        if(curPart.first == (prevPart.first + deltaS[i][0] + BOARD_WIDTH) % BOARD_WIDTH
        && curPart.second == (prevPart.second + deltaS[i][1] + BOARD_HEIGHT) % BOARD_HEIGHT){
          angle = deltaS[i][2];
          break;
        }
      }

      dst.x = 32 * curPart.first;
      dst.y = 32 * curPart.second;

      sTail.RenderEx(renderer, &dst, angle);
    }
    else{
      auto &nextPart = *(it + 1);
      auto &prevPart = *(it - 1);

      bool turn = false;
      if(prevPart.first == nextPart.first)
        angle = 90;
      else if(prevPart.second == nextPart.second)
        angle = 0;
      else
        turn = true;
      
      if(!turn){
        dst.x = 32 * curPart.first;
        dst.y = 32 * curPart.second;
        sBody.RenderEx(renderer, &dst, angle);
      }
      else{
        bool _up = false, _down = false, _left = false, _right = false;
        if((curPart.first == nextPart.first && (curPart.second - 1 + BOARD_HEIGHT) % BOARD_HEIGHT == nextPart.second)
        || (curPart.first == prevPart.first && (curPart.second - 1 + BOARD_HEIGHT) % BOARD_HEIGHT == prevPart.second))
          _up = true;
        if((curPart.first == nextPart.first && (curPart.second + 1) % BOARD_HEIGHT == nextPart.second)
        || (curPart.first == prevPart.first && (curPart.second + 1) % BOARD_HEIGHT == prevPart.second))
          _down = true;
        if(((curPart.first - 1 + BOARD_WIDTH) % BOARD_WIDTH == nextPart.first && curPart.second == nextPart.second)
        || ((curPart.first - 1 + BOARD_WIDTH) % BOARD_WIDTH == prevPart.first && curPart.second == prevPart.second))
          _left = true;
        if(((curPart.first + 1) % BOARD_WIDTH == nextPart.first && curPart.second == nextPart.second)
        || ((curPart.first + 1) % BOARD_WIDTH == prevPart.first && curPart.second == prevPart.second))
          _right = true;

        if(_up && _right)
          angle = 0;
        if(_right && _down)
          angle = 90;
        if(_down && _left)
          angle = 180;
        if(_left && _up)
          angle = 270;

        dst.x = 32 * curPart.first;
        dst.y = 32 * curPart.second;

        sBodyTurn.RenderEx(renderer, &dst, angle);
      }
    }
  }

  // food
  sFood.Render(renderer, foodX * 32, foodY * 32, &dst);
}

void Snake::Init(SDL_Renderer* renderer){
  sHead.LoadTextureFromFile("images/head.png", renderer);
  sBody.LoadTextureFromFile("images/body.png", renderer);
  sBodyTurn.LoadTextureFromFile("images/body_turn.png", renderer);
  sTail.LoadTextureFromFile("images/tail.png", renderer);
  sFood.LoadTextureFromFile("images/food.png", renderer);
}

void Snake::Reset(){
  gameTick = 0;
  dx = 1;
  dy = 0;

  while(!snakeQueue.empty())
    snakeQueue.pop_back();

  snakeQueue.push_back(make_pair(7, 5));
  snakeQueue.push_back(make_pair(6, 5));
  snakeQueue.push_back(make_pair(5, 5));

  FoodGen();
}
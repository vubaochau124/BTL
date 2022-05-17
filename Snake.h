#ifndef SNAKE_H
#define SNAKE_H

#include "GameBase.h"
#include "Button.h"
#include "Texture.h"

class Snake{
public:
  Snake();
  ~Snake();

  void Move(int moveType);

  bool GameTick();
  void FoodGen();

  void Draw(SDL_Renderer* renderer);
  void Init(SDL_Renderer* renderer);
  void Reset();

private:
  Texture sHead;
  Texture sBody;
  Texture sBodyTurn;
  Texture sTail;
  Texture sFood;

  int gameTick = 0;
  int dx = 1;
  int dy = 0;
  int foodX;
  int foodY;

  int MOVE_TIME = 200;

  deque< pair<int, int> > snakeQueue;
};

#endif
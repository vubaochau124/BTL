#ifndef SNAKE_H
#define SNAKE_H

#include "Texture.h"

class Snake{
public:
  Snake();
  ~Snake();

  void Init(SDL_Renderer* renderer);
  void Draw(SDL_Renderer* renderer);

  void Move(int moveType);
  void ForceMove();
  bool checkMove();

  void Growth();

  pair<int,int> GetHeadPos();
  pair<int,int> GetTailPos();
  int GetDirection();

private:

  Texture head;
  Texture headOpen;
  Texture body;
  Texture tail;
  Texture bodyTurn;

  SDL_Rect headclip = {0, 0, 32, 32};
  SDL_Rect bodyclip = {0, 0, 32, 32};
  SDL_Rect tailclip = {0, 0, 32, 32};

  int length;
  int direction;
  
  pair<int, int> currentSnake[MAX_LENGTH];
  pair<int, int> lastTail;
};

#endif
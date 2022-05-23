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
  void ProgressBar(SDL_Renderer* renderer);

  bool GameTick();
  void FoodGen();
  void LevelGen();
  bool IsFull();

  void Draw(SDL_Renderer* renderer);
  void Init(SDL_Renderer* renderer);
  void Reset(int _level);
  void HighScore(int highScore);
  int GetLevel();

private:
  Texture sHead;
  Texture sBody;
  Texture sBodyTurn;
  Texture sTail;
  Texture sFood;
  Texture sWall;
  Texture sScore[10];

  int gameTick = 0;
  int dx = 1;
  int dy = 0;
  int foodX;
  int foodY;
  int level;
  int foodCount;
  int bigFoodX;
  int bigFoodY;
  int bigFoodTick = 0;
  int highScore;

  int score;

  int MOVE_TIME = 200;

  deque< pair<int, int> > snakeQueue;
  vector< pair <int, int> > levelWall[6];
  vector< pair<int, int> > levelSnakeStart[6];

};

#endif
#ifndef GAMEBASE_H
#define GAMEBASE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include <deque>
#include <vector>

using namespace std;

const int SCREEN_WIDTH = 960;
const int SCREEN_HEIGHT = 640;

const int BUTTON_WIDTH = 150;
const int BUTTON_HEIGHT = 75;

//board

const int BOARD_WIDTH = 20;
const int BOARD_HEIGHT = 15;

const int OFFSET = 30;

const int MAX_FOOD_COUNT = 18;

enum Block{
    FOOD,
    FREE,
    WALL,
    SNAKE
};

enum ButtonSprite{
    BUTTON_DEFAULT = 0,
    BUTTON_HOVERED = 1,
    BUTTON_DOWN = 2,
    BUTTON_TOTAL = 3
};

enum Screen{
	HOME,
	CLASSIC,
    MODE,
    CAMPAIGN,
    OVER,
    CONGRATULATION,
    ELSE
};

enum Move{
    LEFT,
    UP,
    RIGHT,
    DOWN
};

#endif
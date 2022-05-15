#ifndef GAMEBASE_H
#define GAMEBASE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <string>
#include <algorithm>
#include <ctime>
#include <cstdlib>

using namespace std;

const int SCREEN_WIDTH = 960;
const int SCREEN_HEIGHT = 640;

const int BUTTON_WIDTH = 150;
const int BUTTON_HEIGHT = 75;

const int MAX_LENGTH = 1000;

const int ADDTIME = 100;

//board

const int BOARD_X = 64;
const int BOARD_Y = 64;
const int BOARD_WIDTH = 20;
const int BOARD_HEIGHT = 15;

enum Block{
    FOOD,
    FREE,
    WALL,
    SNAKE
};

enum ButtonSprite{
    BUTTON_OUT = 0,
    BUTTON_OVER = 1,
    BUTTON_DOWN = 2,
    BUTTON_TOTAL = 3
};

enum Screen{
	QUIT_SCREEN,
	HOME_SCREEN,
	PAUSE_SCREEN,
	GAME_SCREEN
};

enum Move{
    LEFT,
    RIGHT,
    UP,
    DOWN
};

#endif
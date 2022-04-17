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

const int SCREEN_WIDTH = 1080;
const int SCREEN_HEIGHT = 720;

const int BUTTON_WIDTH = 200;
const int BUTTON_HEIGHT = 100;

enum ButtonSprite{
    BUTTON_OUT = 0,
    BUTTON_OVER = 1,
    BUTTON_DOWN = 2,
    BUTTON_TOTAL = 3
};

#endif
#ifndef BOARD_H
#define BOARD_H

#include "GameBase.h"
#include "Texture.h"
#include "Snake.h"

class Board{
    public:
        Board();
        ~Board();
        
        void Reset();
        bool IsEnded();
        void Init();

        void Update(int checkType);
        void Move(int moveType);
        void ForceMove();
        int MoveCheck(int moveType);

        void SpawnFood();

        void DrawBoard(SDL_Renderer* renderer);
        void TextureInit(SDL_Renderer* renderer);

    private:
        int board[BOARD_WIDTH][BOARD_HEIGHT];

        pair<int, int> food;

        Texture boardTex;
        Texture playField;
        Texture foodTex;

        SDL_Rect boardTexClip = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
        SDL_Rect playFieldClip = {0, 0, 832, 512};
        SDL_Rect foodTexClip = {0, 0, 32, 32};

        Snake snake;
};

#endif
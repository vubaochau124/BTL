#ifndef BUTTON_H
#define BUTTON_H

#include "Texture.h"

class Button{
    public:
        ~Button();
        Button(int x, int y, int w, int h);

        int buttonSprite;

        bool MouseOnButton(int x, int y);
        void Render(SDL_Renderer* renderer, Texture buttonTexture, SDL_Rect* clip);
        void HandleEvent(SDL_Event* e);
    private:
        SDL_Point buttonPosition;
        int buttonWidth;
        int buttonHeight;
};

#endif
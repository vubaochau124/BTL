#include "Button.h"

Button::Button(int x, int y, int w, int h){
    buttonSprite = BUTTON_OUT;
    buttonPosition.x = x;
    buttonPosition.y = y; 
    buttonWidth = w;
    buttonHeight = h;
}

Button::~Button(){

}

bool Button::MouseOnButton(int x, int y){
    bool OnButton = true;
    if (x < buttonPosition.x)
        OnButton = false;
    if (x > buttonPosition.x + buttonWidth)
        OnButton = false;
    if (y < buttonPosition.y )
        OnButton = false;
    if (y > buttonPosition.y + buttonHeight)
        OnButton = false;  
    return OnButton;
}

void Button::Render(SDL_Renderer* renderer, Texture buttonTexture, SDL_Rect* clip){
    buttonTexture.Render(renderer, buttonPosition.x, buttonPosition.y, clip);
}

void Button::HandleEvent(SDL_Event* e){
    if(e->type == SDL_MOUSEMOTION || e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEBUTTONUP){
        int x, y;
        SDL_GetMouseState(&x, &y);

        if (MouseOnButton(x, y)){
            if (e->type == SDL_MOUSEMOTION)
                buttonSprite = BUTTON_OVER;
            if (e->type == SDL_MOUSEBUTTONDOWN)
                buttonSprite = BUTTON_DOWN;
        }
        else
            buttonSprite = BUTTON_OUT;
    }
}


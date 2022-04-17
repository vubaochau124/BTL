#include "Texture.h"

Texture::Texture(){
    texture = NULL;
    width = 0;
    height = 0;
}

Texture::~Texture(){
    FreeTexture();
}

void Texture::FreeTexture(){
    texture = NULL;
    width = 0;
    height = 0;
}

void Texture::LoadTextureFromFile(string path, SDL_Renderer* renderer){
    SDL_Texture* tmpTexture = NULL;
    SDL_Surface* tmpSurface = IMG_Load(path.c_str());

    if(tmpSurface == NULL){
        cout << "Cannot load img" << IMG_GetError() << '\n';
    }
    else{
        tmpTexture = SDL_CreateTextureFromSurface(renderer, tmpSurface);
        if (tmpTexture == NULL)
            cout << "Cannot load texture" << SDL_GetError() << '\n';
        else{
            width = tmpSurface->w;
            height = tmpSurface->h;
        }
        SDL_FreeSurface(tmpSurface);
    }
    texture = tmpTexture;
}

void Texture::Render(SDL_Renderer* renderer, int x, int y, SDL_Rect* clip){
    SDL_Rect renderRect = {x, y, width, height};
    if (clip != NULL){
        renderRect.w = clip->w;
        renderRect.h = clip->h;
    }
    SDL_RenderCopy(renderer, texture, NULL, &renderRect);
}

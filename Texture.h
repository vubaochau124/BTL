#ifndef TEXTURE_H
#define TEXTURE_H

#include "GameBase.h"

class Texture{
    public:
        Texture();
        ~Texture();
        
        SDL_Texture* texture;
        int width;
        int height;

        void FreeTexture();
        void LoadTextureFromFile(string path, SDL_Renderer* renderer);
        void Render(SDL_Renderer* renderer, int x, int y, SDL_Rect* clip);

};

#endif
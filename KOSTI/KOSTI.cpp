#include "SDL.h"
#include "stdlib.h"
#include <SDL_ttf.h>
#include "SDL_image.h"
#include "ctime"
#include "SDL_mixer.h"
#include <stdio.h>
#include <locale.h>
#include <windows.h>
bool isSet(int x, int y) {
    SDL_Rect buttonRect; 
    buttonRect.x = 1214;  
    buttonRect.y = 0;
    buttonRect.w = 80;  
    buttonRect.h = 80;
    if (x >= buttonRect.x && x <= (buttonRect.x + buttonRect.w) && y >= buttonRect.y && y <= (buttonRect.y + buttonRect.h))
    { return true; }
    return false;
}
bool isRule(int x, int y) {
    SDL_Rect buttonRect;
    buttonRect.x = 1374;
    buttonRect.y = 0;
    buttonRect.w = 80;
    buttonRect.h = 80;
    if (x >= buttonRect.x && x <= (buttonRect.x + buttonRect.w) && y >= buttonRect.y && y <= (buttonRect.y + buttonRect.h))
    {
        return true;
    }
    return false;
}
bool isQuit(int x, int y) {
    SDL_Rect buttonRect;
    buttonRect.x = 1054;
    buttonRect.y = 0;
    buttonRect.w = 80;
    buttonRect.h = 80;
    if (x >= buttonRect.x && x <= (buttonRect.x + buttonRect.w) && y >= buttonRect.y && y <= (buttonRect.y + buttonRect.h))
    {
        return true;
    }
    return false;
}
void draw_NK(SDL_Renderer*& renderer, SDL_Texture* texture)
{
    SDL_Rect rect = { 1214, 0, 80, 80 };
    SDL_RenderCopy(renderer, texture, NULL, &rect);
}
void draw_Rule(SDL_Renderer*& renderer, SDL_Texture* texture)
{
    SDL_Rect rect = { 1374, 0, 80, 80 };
    SDL_RenderCopy(renderer, texture, NULL, &rect);
}
void draw_Quit(SDL_Renderer*& renderer, SDL_Texture* texture)
{
    SDL_Rect rect = { 1054, 0, 80, 80 };
    SDL_RenderCopy(renderer, texture, NULL, &rect);
}
int main(int argc, char** argv) {
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;
    window = SDL_CreateWindow(u8"Кости", 0, 30, 1535, 800, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, 0);
    SDL_Surface* fonImage = IMG_Load("m1.bmp"); //самая первая картинка с меню
    SDL_SetColorKey(fonImage, SDL_TRUE, SDL_MapRGB(fonImage->format, 255, 255, 255));
    SDL_Texture* fonTexture = SDL_CreateTextureFromSurface(renderer, fonImage);
    SDL_RenderCopy(renderer, fonTexture, NULL, NULL);
    SDL_RenderPresent(renderer);

    SDL_Surface* NKImage = IMG_Load("NK.bmp"); //нажали на настройки
    SDL_SetColorKey(NKImage, SDL_TRUE, SDL_MapRGB(NKImage->format, 255, 255, 255));
    SDL_Texture* NKTexture = SDL_CreateTextureFromSurface(renderer, NKImage);
    SDL_FreeSurface(NKImage);

    SDL_Surface* RuleImage = IMG_Load("Rule.bmp"); //нажали на правила
    SDL_SetColorKey(RuleImage, SDL_TRUE, SDL_MapRGB(RuleImage->format, 255, 255, 255));
    SDL_Texture* RuleTexture = SDL_CreateTextureFromSurface(renderer, RuleImage);
    SDL_FreeSurface(RuleImage);

    SDL_Surface* QuitImage = IMG_Load("Quit.bmp"); //кнопка выхода (если в начале, то из приложения, если нет, то в начало)
    SDL_SetColorKey(QuitImage, SDL_TRUE, SDL_MapRGB(QuitImage->format, 255, 255, 255));
    SDL_Texture* QuitTexture = SDL_CreateTextureFromSurface(renderer, QuitImage);
    SDL_FreeSurface(QuitImage);

    SDL_Surface* R1Image = IMG_Load("R1.bmp"); //первая стр правил
    SDL_SetColorKey(R1Image, SDL_TRUE, SDL_MapRGB(R1Image->format, 255, 255, 255));
    SDL_Texture* R1Texture = SDL_CreateTextureFromSurface(renderer, R1Image);
    SDL_FreeSurface(R1Image);

    SDL_Surface* R2Image = IMG_Load("R2.bmp"); //вторая стр правил
    SDL_SetColorKey(R2Image, SDL_TRUE, SDL_MapRGB(R2Image->format, 255, 255, 255));
    SDL_Texture* R2Texture = SDL_CreateTextureFromSurface(renderer, R2Image);
    SDL_FreeSurface(R2Image);


    SDL_Event event;
    bool quit = false;
	while (!quit)
	{
		while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) { quit = true; }
            if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT)
            {
                int x, y;
                SDL_GetMouseState(&x, &y);
                if (isSet(x, y)) { 
                    draw_NK(renderer, NKTexture); 
                    SDL_RenderPresent(renderer);
                    SDL_Delay(1000);
                }
                if (isRule(x, y)) {
                    draw_Rule (renderer, RuleTexture);
                    SDL_RenderPresent(renderer);
                    SDL_Delay(1000);
                    //идём дальше
                    while (!isQuit(x, y)) { //DOESNT WORK!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!1
                        /*SDL_RenderClear(renderer);
                        SDL_DestroyTexture(fonTexture);*/
                        SDL_GetMouseState(&x, &y);
                        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
                        SDL_RenderClear(renderer);
                        draw_Quit(renderer, QuitTexture);
                        SDL_RenderCopy(renderer, R1Texture, NULL, NULL);
                        SDL_RenderPresent(renderer);
                    }
                }
                if (isQuit(x, y)) {
                    draw_Quit(renderer, QuitTexture);
                    SDL_RenderPresent(renderer);
                    SDL_Delay(1000);
                    quit = true;
                }
            }
		}
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, fonTexture, NULL, NULL);
        SDL_RenderPresent(renderer);
	}
    SDL_RenderClear(renderer);
    SDL_DestroyTexture(QuitTexture);
    SDL_DestroyTexture(RuleTexture);
    SDL_DestroyTexture(NKTexture);
    SDL_DestroyTexture(fonTexture);
    SDL_FreeSurface(fonImage);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
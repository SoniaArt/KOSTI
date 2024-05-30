#include "SDL.h"
#include "stdlib.h"
#include <SDL_ttf.h>
#include "SDL_image.h"
#include "ctime"
#include "SDL_mixer.h"
#include <stdio.h>
#include <locale.h>
#include <windows.h>
enum State {
    MENU,
    GAME,
    CHOICE_GAME_MODE,
    CHOICE_DIFFICULTY_LEVEL,
    CHOICE_BONUS_GAME,
    BONUS_GAME,
    BONUS_GAME_1,
    BONUS_GAME_1_2,
    BONUS_GAME_2,
    BONUS_GAME_2_2,
    BONUS_GAME_3,
    BONUS_GAME_3_2,
    MAIN_GAME,
    EXIT,
    SETTINGS,
    RULES,
    RULES_2,
    PROGRESS,
};
bool isHit(int x, int y, SDL_Rect rect) {
    if (x >= rect.x && x <= (rect.x + rect.w) && y >= rect.y && y <= (rect.y + rect.h))
    {
        return true;
    }
    return false;
}
void draw(SDL_Renderer*& renderer, SDL_Texture* texture, SDL_Rect rect)
{
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

    SDL_Surface* rightArrowImage = IMG_Load("rightArrow.bmp"); //стрелка вправо на 1-й странице правил
    SDL_SetColorKey(rightArrowImage, SDL_TRUE, SDL_MapRGB(rightArrowImage->format, 255, 255, 255));
    SDL_Texture* rightArrowTexture = SDL_CreateTextureFromSurface(renderer, rightArrowImage);
    SDL_FreeSurface(rightArrowImage);

    SDL_Surface* leftArrowImage = IMG_Load("leftArrow.bmp"); //стрелка влево на 2-й странице правил
    SDL_SetColorKey(leftArrowImage, SDL_TRUE, SDL_MapRGB(leftArrowImage->format, 255, 255, 255));
    SDL_Texture* leftArrowTexture = SDL_CreateTextureFromSurface(renderer, leftArrowImage);
    SDL_FreeSurface(leftArrowImage);



    SDL_Surface* startGameImage = IMG_Load("startGame.bmp"); //начать игру
    SDL_SetColorKey(startGameImage, SDL_TRUE, SDL_MapRGB(startGameImage->format, 255, 255, 255));
    SDL_Texture* startGameTexture = SDL_CreateTextureFromSurface(renderer, startGameImage);
    SDL_FreeSurface(startGameImage);

    SDL_Surface* checkProgressImage = IMG_Load("checkProgress.bmp"); //посмотреть прогресс
    SDL_SetColorKey(checkProgressImage, SDL_TRUE, SDL_MapRGB(checkProgressImage->format, 255, 255, 255));
    SDL_Texture* checkProgressTexture = SDL_CreateTextureFromSurface(renderer, checkProgressImage);
    SDL_FreeSurface(checkProgressImage);



    SDL_Surface* choiceGameModeImage = IMG_Load("choiceGameMode.bmp"); //окно выбора игры
    SDL_SetColorKey(choiceGameModeImage, SDL_TRUE, SDL_MapRGB(choiceGameModeImage->format, 255, 255, 255));
    SDL_Texture* choiceGameModeTexture = SDL_CreateTextureFromSurface(renderer, choiceGameModeImage);
    SDL_FreeSurface(choiceGameModeImage);

    SDL_Surface* PlayerPlayerImage = IMG_Load("PlayerPlayer.bmp"); //игрок игрок
    SDL_SetColorKey(PlayerPlayerImage, SDL_TRUE, SDL_MapRGB(PlayerPlayerImage->format, 255, 255, 255));
    SDL_Texture* PlayerPlayerTexture = SDL_CreateTextureFromSurface(renderer, PlayerPlayerImage);
    SDL_FreeSurface(PlayerPlayerImage);

    SDL_Surface* PlayerCompImage = IMG_Load("PlayerComp.bmp"); //игрок компьютер
    SDL_SetColorKey(PlayerCompImage, SDL_TRUE, SDL_MapRGB(PlayerCompImage->format, 255, 255, 255));
    SDL_Texture* PlayerCompTexture = SDL_CreateTextureFromSurface(renderer, PlayerCompImage);
    SDL_FreeSurface(PlayerCompImage);



    SDL_Surface* choiceDifficultyLevelImage = IMG_Load("choiceDifficultyLevel.bmp"); //окно выбора уровня
    SDL_SetColorKey(choiceDifficultyLevelImage, SDL_TRUE, SDL_MapRGB(choiceDifficultyLevelImage->format, 255, 255, 255));
    SDL_Texture* choiceDifficultyLevelTexture = SDL_CreateTextureFromSurface(renderer, choiceDifficultyLevelImage);
    SDL_FreeSurface(choiceDifficultyLevelImage);

    SDL_Surface* easyImage = IMG_Load("easy.bmp"); //легкий уровень
    SDL_SetColorKey(easyImage, SDL_TRUE, SDL_MapRGB(easyImage->format, 255, 255, 255));
    SDL_Texture* easyTexture = SDL_CreateTextureFromSurface(renderer, easyImage);
    SDL_FreeSurface(easyImage);

    SDL_Surface* mediumImage = IMG_Load("medium.bmp"); //средний уровень
    SDL_SetColorKey(mediumImage, SDL_TRUE, SDL_MapRGB(mediumImage->format, 255, 255, 255));
    SDL_Texture* mediumTexture = SDL_CreateTextureFromSurface(renderer, mediumImage);
    SDL_FreeSurface(mediumImage);
    
    SDL_Surface* hardImage = IMG_Load("hard.bmp"); //сложный уровень
    SDL_SetColorKey(hardImage, SDL_TRUE, SDL_MapRGB(hardImage->format, 255, 255, 255));
    SDL_Texture* hardTexture = SDL_CreateTextureFromSurface(renderer, hardImage);
    SDL_FreeSurface(hardImage);

    SDL_Surface* veryHardImage = IMG_Load("veryHard.bmp"); //очень сложный уровень
    SDL_SetColorKey(veryHardImage, SDL_TRUE, SDL_MapRGB(veryHardImage->format, 255, 255, 255));
    SDL_Texture* veryHardTexture = SDL_CreateTextureFromSurface(renderer, veryHardImage);
    SDL_FreeSurface(veryHardImage);



    SDL_Surface* choiceBonusGameImage = IMG_Load("choiceBonusGame.bmp"); //окно предложения сыграть в бонусную игру
    SDL_SetColorKey(choiceBonusGameImage, SDL_TRUE, SDL_MapRGB(choiceBonusGameImage->format, 255, 255, 255));
    SDL_Texture* choiceBonusGameTexture = SDL_CreateTextureFromSurface(renderer, choiceBonusGameImage);
    SDL_FreeSurface(choiceBonusGameImage);

    SDL_Surface* yesImage = IMG_Load("yes.bmp"); //кнопка да
    SDL_SetColorKey(yesImage, SDL_TRUE, SDL_MapRGB(yesImage->format, 255, 255, 255));
    SDL_Texture* yesTexture = SDL_CreateTextureFromSurface(renderer, yesImage);
    SDL_FreeSurface(yesImage);

    SDL_Surface* noImage = IMG_Load("no.bmp"); //кнопка нет
    SDL_SetColorKey(noImage, SDL_TRUE, SDL_MapRGB(noImage->format, 255, 255, 255));
    SDL_Texture* noTexture = SDL_CreateTextureFromSurface(renderer, noImage);
    SDL_FreeSurface(noImage);



    SDL_Surface* bonusGameImage = IMG_Load("bonusGame.bmp"); //окно бонусной игры с выбором кол-ва кубиков
    SDL_SetColorKey(bonusGameImage, SDL_TRUE, SDL_MapRGB(bonusGameImage->format, 255, 255, 255));
    SDL_Texture* bonusGameTexture = SDL_CreateTextureFromSurface(renderer, bonusGameImage);
    SDL_FreeSurface(bonusGameImage);

    SDL_Surface* oneCubeImage = IMG_Load("oneCube.bmp"); //один кубик
    SDL_SetColorKey(oneCubeImage, SDL_TRUE, SDL_MapRGB(oneCubeImage->format, 255, 255, 255));
    SDL_Texture* oneCubeTexture = SDL_CreateTextureFromSurface(renderer, oneCubeImage);
    SDL_FreeSurface(oneCubeImage);

    SDL_Surface* twoCubeImage = IMG_Load("twoCube.bmp"); //два кубика
    SDL_SetColorKey(twoCubeImage, SDL_TRUE, SDL_MapRGB(twoCubeImage->format, 255, 255, 255));
    SDL_Texture* twoCubeTexture = SDL_CreateTextureFromSurface(renderer, twoCubeImage);
    SDL_FreeSurface(twoCubeImage);

    SDL_Surface* threeCubeImage = IMG_Load("threeCube.bmp"); //три кубика
    SDL_SetColorKey(threeCubeImage, SDL_TRUE, SDL_MapRGB(threeCubeImage->format, 255, 255, 255));
    SDL_Texture* threeCubeTexture = SDL_CreateTextureFromSurface(renderer, threeCubeImage);
    SDL_FreeSurface(threeCubeImage);

    SDL_Surface* bonusGame1Image = IMG_Load("bonusGame1.bmp"); //выбран 1 кубик
    SDL_SetColorKey(bonusGame1Image, SDL_TRUE, SDL_MapRGB(bonusGame1Image->format, 255, 255, 255));
    SDL_Texture* bonusGame1Texture = SDL_CreateTextureFromSurface(renderer, bonusGame1Image);
    SDL_FreeSurface(bonusGame1Image);

    SDL_Surface* bonusGame1_2Image = IMG_Load("bonusGame1_2.bmp"); //выбран 1 кубик
    SDL_SetColorKey(bonusGame1_2Image, SDL_TRUE, SDL_MapRGB(bonusGame1_2Image->format, 255, 255, 255));
    SDL_Texture* bonusGame1_2Texture = SDL_CreateTextureFromSurface(renderer, bonusGame1_2Image);
    SDL_FreeSurface(bonusGame1_2Image);

    SDL_Surface* bonusGame2Image = IMG_Load("bonusGame2.bmp"); //выбрано 2 кубика
    SDL_SetColorKey(bonusGame2Image, SDL_TRUE, SDL_MapRGB(bonusGame2Image->format, 255, 255, 255));
    SDL_Texture* bonusGame2Texture = SDL_CreateTextureFromSurface(renderer, bonusGame2Image);
    SDL_FreeSurface(bonusGame2Image);

    SDL_Surface* bonusGame2_2Image = IMG_Load("bonusGame2_2.bmp"); //выбрано 2 кубика
    SDL_SetColorKey(bonusGame2_2Image, SDL_TRUE, SDL_MapRGB(bonusGame2_2Image->format, 255, 255, 255));
    SDL_Texture* bonusGame2_2Texture = SDL_CreateTextureFromSurface(renderer, bonusGame2_2Image);
    SDL_FreeSurface(bonusGame2_2Image);

    SDL_Surface* bonusGame3Image = IMG_Load("bonusGame3.bmp"); //выбрано 3 кубика
    SDL_SetColorKey(bonusGame3Image, SDL_TRUE, SDL_MapRGB(bonusGame3Image->format, 255, 255, 255));
    SDL_Texture* bonusGame3Texture = SDL_CreateTextureFromSurface(renderer, bonusGame3Image);
    SDL_FreeSurface(bonusGame3Image);

    SDL_Surface* bonusGame3_2Image = IMG_Load("bonusGame3_2.bmp"); //выбрано 3 кубика
    SDL_SetColorKey(bonusGame3_2Image, SDL_TRUE, SDL_MapRGB(bonusGame3_2Image->format, 255, 255, 255));
    SDL_Texture* bonusGame3_2Texture = SDL_CreateTextureFromSurface(renderer, bonusGame3_2Image);
    SDL_FreeSurface(bonusGame3_2Image);


    SDL_Surface* redNumberImage = IMG_Load("redNumber.bmp"); //выбрано 3 кубика
    SDL_SetColorKey(redNumberImage, SDL_TRUE, SDL_MapRGB(redNumberImage->format, 255, 255, 255));
    SDL_Texture* redNumberTexture = SDL_CreateTextureFromSurface(renderer, redNumberImage);
    SDL_FreeSurface(redNumberImage);


    //   МЕСТОПОЛОЖЕНИE КНОПОК     ///    
    SDL_Rect Quit = { 1054, 0, 80, 80 };
    SDL_Rect Settings = { 1214, 0, 80, 80 };
    SDL_Rect checkProgress = { 235, 450, 1179, 100 };

    SDL_Rect Rules = { 1374, 0, 80, 80 };
    SDL_Rect rightArrow = { 1374, 720, 80, 80 };
    SDL_Rect leftArrow = { 1374, 720, 80, 80 };

    SDL_Rect startGame = { 338, 297, 939, 100 };
    SDL_Rect choiceGameMode = { 0, 0, 1535, 800 };
    SDL_Rect playerPlayer = { 298, 477, 939, 100 };
    SDL_Rect playerComp = { 298, 315, 939, 100 };


    SDL_Rect choiceDifficultyLevel = { 0, 0, 1535, 800 };
    SDL_Rect easy = {59, 229, 310,460};
    SDL_Rect medium = {422, 229, 310, 460};
    SDL_Rect hard = {784, 229, 310,460};
    SDL_Rect veryHard = {1144, 229, 310, 460};

    SDL_Rect choiceBonusGame = { 0, 0, 1535, 800 };
    SDL_Rect yes = { 298, 315, 939,  100};
    SDL_Rect no = { 298, 477, 939, 100 };


    SDL_Rect bonusGame = { 0, 0, 1535, 800 };
    SDL_Rect oneCube = { 594, 252, 60, 60 };
    SDL_Rect twoCube = { 728, 252, 60, 60 };
    SDL_Rect threeCube = { 862, 252, 60, 60 };


    SDL_Rect three =     { 10, 431, 85, 60 };
    SDL_Rect four =      { 105, 431, 85, 60 };
    SDL_Rect five =      { 200, 431, 85, 60 };
    SDL_Rect six =       { 295, 431, 85, 60 };
    SDL_Rect seven =     { 390, 431, 85, 60 };
    SDL_Rect eight =     { 485, 431, 85, 60 };
    SDL_Rect nine =      { 580, 431, 85, 60 };
    SDL_Rect ten =       { 675, 431, 85, 60 };
    SDL_Rect eleven =    { 770, 431, 85, 60 };
    SDL_Rect twelve =    { 865, 431, 85, 60 };
    SDL_Rect thirteen =  { 960, 431, 85, 60 };
    SDL_Rect fourteen = { 1055, 431, 85, 60 };
    SDL_Rect fifteen = { 1150, 431, 85, 60 };
    SDL_Rect sixteen = { 1245, 431, 85, 60 };
    SDL_Rect seventeen = { 1340, 431, 85, 60 };
    SDL_Rect eightteen = { 1435, 431, 85, 60 };



    SDL_Event event;
    State currentState = MENU;
    bool quit = false;
    int x, y;
    int choiceMode = 0;
    int choiceDiffLevel = 0;
    while (!quit)
    {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) { quit = true; }
            switch (currentState) 
            {
                case MENU:
                    SDL_RenderCopy(renderer, fonTexture, NULL, NULL);
                    if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT)
                    {
                        SDL_GetMouseState(&x, &y);
                        if (isHit(x, y, Quit))
                        {quit = true;}
                        if (isHit(x, y, Rules)) {
                            currentState = RULES;
                            break;
                        }
                        if (isHit(x, y, Settings)) {
                            currentState = SETTINGS;
                            break;
                        }
                        if (isHit(x, y, startGame)) {
                            currentState = CHOICE_GAME_MODE;
                            break;
                        }
                        
                    }
                    if (event.type == SDL_MOUSEMOTION)
                    {
                        SDL_GetMouseState(&x, &y);
                        if (isHit(x, y, Quit)) {
                            draw(renderer, QuitTexture, Quit);
                            break;
                        }
                        if (isHit(x, y, Rules)) {
                            draw(renderer, RuleTexture, Rules);
                            break;
                        }
                        if (isHit(x, y, Settings)) {
                            draw(renderer, NKTexture, Settings);
                            break;
                        }
                        if (isHit(x, y, startGame)) {
                            draw(renderer, startGameTexture, startGame);
                            break;
                        }
                        if (isHit(x, y, checkProgress)) {
                            draw(renderer, checkProgressTexture, checkProgress);
                            break;
                        }
                    }
                    
                    break;
                case SETTINGS: break;
                    //event.type == SDL_MOUSEBUTTONDOWN && 
                case RULES: 
                    SDL_RenderCopy(renderer, R1Texture, NULL, NULL);
                    if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT) {
                        SDL_GetMouseState(&x, &y);
                        if(isHit(x, y, Quit))
                        {
                            currentState = MENU; break;
                        }
                        if (isHit(x, y, Settings))
                        {
                            currentState = SETTINGS; break;
                        }
                        if (isHit(x, y, rightArrow))
                        {
                            currentState = RULES_2; break;
                        }   
                    }
                    if (event.type == SDL_MOUSEMOTION)
                    {
                        SDL_GetMouseState(&x, &y);
                        if (isHit(x, y, Quit)) {
                            draw(renderer, QuitTexture, Quit);
                            break;
                        }
                        if (isHit(x, y, Settings)) {
                            draw(renderer, NKTexture, Settings);
                            break;
                        }
                        if (isHit(x, y, rightArrow)) {
                            draw(renderer, rightArrowTexture, rightArrow); break;
                        }

                    }
                    break;
                case RULES_2:
                    SDL_RenderCopy(renderer, R2Texture, NULL, NULL);
                    if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT) {
                        SDL_GetMouseState(&x, &y);
                        if (isHit(x, y, Quit))
                        {
                            currentState = MENU; break;
                        }
                        if (isHit(x, y, Settings))
                        {
                            currentState = SETTINGS; break;
                        }
                        if (isHit(x, y, leftArrow))
                        {
                            currentState = RULES; break;
                        }
                    }
                    if (event.type == SDL_MOUSEMOTION)
                    {
                        SDL_GetMouseState(&x, &y);
                        if (isHit(x, y, Quit)) {
                            draw(renderer, QuitTexture, Quit);
                            break;
                        }
                        if (isHit(x, y, Settings)) {
                            draw(renderer, NKTexture, Settings);
                            break;
                        }
                        if (isHit(x, y, leftArrow)) {
                            draw(renderer, leftArrowTexture, leftArrow);
                            break;
                        }
                        if (isHit(x, y, Settings)) {
                            draw(renderer, NKTexture, Settings);
                            break;
                        }
                    }
                    break;
                case CHOICE_GAME_MODE:
                    draw(renderer, choiceGameModeTexture, choiceGameMode);
                    if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT)
                    {
                        SDL_GetMouseState(&x, &y);
                        if (isHit(x, y, Quit))
                        {
                            currentState = MENU;
                            break;
                        }
                        if (isHit(x, y, Rules)) {
                            currentState = RULES;
                            break;
                        }
                        if (isHit(x, y, Settings)) {
                            currentState = SETTINGS;
                            break;
                        }
                        if (isHit(x, y, playerPlayer)) {
                            currentState = CHOICE_DIFFICULTY_LEVEL;
                            break;
                        }
                        if (isHit(x, y, playerComp)) {
                            currentState = CHOICE_DIFFICULTY_LEVEL;
                            break;
                        }
                    }
                    if (event.type == SDL_MOUSEMOTION)
                    {
                        SDL_GetMouseState(&x, &y);
                        if (isHit(x, y, Quit)) {
                            draw(renderer, QuitTexture, Quit);
                            break;
                        }
                        if (isHit(x, y, Settings)) {
                            draw(renderer, NKTexture, Settings);
                            break;
                        }
                        if (isHit(x, y, playerPlayer)) {
                            draw(renderer, PlayerPlayerTexture, playerPlayer);
                            break;
                        }
                        if (isHit(x, y, playerComp)) {
                            draw(renderer, PlayerCompTexture, playerComp);
                            break;
                        }
                        if (isHit(x, y, Rules)) {
                            draw(renderer, RuleTexture, Rules);
                            break;
                        }
                    }
                    break;
                case CHOICE_DIFFICULTY_LEVEL:
                    draw(renderer, choiceDifficultyLevelTexture, choiceDifficultyLevel);
                    if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT)
                    {
                        SDL_GetMouseState(&x, &y);
                        if (isHit(x, y, Quit))
                        {
                            currentState = MENU;
                            break;
                        }
                        if (isHit(x, y, Rules)) {
                            currentState = RULES;
                            break;
                        }
                        if (isHit(x, y, Settings)) {
                            currentState = SETTINGS;
                            break;
                        }
                        if (isHit(x, y, easy)) {
                            //choiceDiffLevel = 1;
                            currentState = CHOICE_BONUS_GAME;
                            break;
                        }
                        if (isHit(x, y, medium)) {
                            //choiceDiffLevel = 2;
                            currentState = CHOICE_BONUS_GAME;
                            break;
                        }
                        if (isHit(x, y, hard)) {
                            //choiceDiffLevel = 3;
                            currentState = CHOICE_BONUS_GAME;
                            break;
                        }
                        if (isHit(x, y, veryHard)) {
                            //choiceDiffLevel = 4;
                            currentState = CHOICE_BONUS_GAME;
                            break;
                        }
                    }
                    if (event.type == SDL_MOUSEMOTION)
                    {
                        SDL_GetMouseState(&x, &y);
                        if (isHit(x, y, Quit)) {
                            draw(renderer, QuitTexture, Quit);
                            break;
                        }
                        if (isHit(x, y, Settings)) {
                            draw(renderer, NKTexture, Settings);
                            break;
                        }
                        if (isHit(x, y, Rules)) {
                            draw(renderer, RuleTexture, Rules);
                            break;
                        }
                        if (isHit(x, y, easy)) {
                            draw(renderer, easyTexture, easy);
                            break;
                        }
                        if (isHit(x, y, medium)) {
                            draw(renderer, mediumTexture, medium);
                            break;
                        }
                        if (isHit(x, y, hard)) {
                            draw(renderer, hardTexture, hard);
                            break;
                        }
                        if (isHit(x, y, veryHard)) {
                            draw(renderer, veryHardTexture, veryHard);
                            break;
                        }
                    }
                    break;
                case CHOICE_BONUS_GAME: 
                    draw(renderer, choiceBonusGameTexture, choiceBonusGame);
                    if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT) {
                        SDL_GetMouseState(&x, &y);
                        if (isHit(x, y, Quit))
                        {
                            currentState = MENU;
                            break;
                        }
                        if (isHit(x, y, Rules)) {
                            currentState = RULES;
                            break;
                        }
                        if (isHit(x, y, Settings)) {
                            currentState = SETTINGS;
                            break;
                        }
                        if (isHit(x, y, yes)) {
                            currentState = BONUS_GAME;
                            break;
                        }
                        if (isHit(x, y, no)) {
                            currentState = MAIN_GAME;
                        }
                    }
                    if (event.type == SDL_MOUSEMOTION) {
                        SDL_GetMouseState(&x, &y);
                        if (isHit(x, y, Quit)) {
                            draw(renderer, QuitTexture, Quit);
                            break;
                        }
                        if (isHit(x, y, Settings)) {
                            draw(renderer, NKTexture, Settings);
                            break;
                        }
                        if (isHit(x, y, Rules)) {
                            draw(renderer, RuleTexture, Rules);
                            break;
                        }
                        if (isHit(x, y, yes)) {
                            draw(renderer, yesTexture, yes);
                            break;
                        }
                        if (isHit(x, y, no)) {
                            draw(renderer, noTexture, no);
                            break;
                        }
                    }
                    break;
                case BONUS_GAME:
                    draw(renderer, bonusGameTexture, bonusGame);
                    if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT) {
                        SDL_GetMouseState(&x, &y);
                        if (isHit(x, y, Quit))
                        {
                            currentState = MENU;
                            break;
                        }
                        if (isHit(x, y, Rules)) {
                            currentState = RULES;
                            break;
                        }
                        if (isHit(x, y, Settings)) {
                            currentState = SETTINGS;
                            break;
                        }
                        if (isHit(x, y, oneCube)) {
                            currentState = BONUS_GAME_1;
                            break;
                        }
                        if (isHit(x, y, twoCube)) {
                            currentState = BONUS_GAME_2;
                            break;
                        }
                        if (isHit(x, y, threeCube)) {
                            currentState = BONUS_GAME_3;
                            break;
                        }

                    }
                    if (event.type == SDL_MOUSEMOTION) {
                        SDL_GetMouseState(&x, &y);
                        if (isHit(x, y, Quit)) {
                            draw(renderer, QuitTexture, Quit);
                            break;
                        }
                        if (isHit(x, y, Settings)) {
                            draw(renderer, NKTexture, Settings);
                            break;
                        }
                        if (isHit(x, y, Rules)) {
                            draw(renderer, RuleTexture, Rules);
                            break;
                        }
                        if (isHit(x, y, oneCube)) {
                            draw(renderer, oneCubeTexture, oneCube);
                            break;
                        }
                        if (isHit(x, y, twoCube)) {
                            draw(renderer, twoCubeTexture, twoCube);
                            break;
                        }
                        if (isHit(x, y, threeCube)) {
                            draw(renderer, threeCubeTexture, threeCube);
                            break;
                        }
                    }
                    break;
                case BONUS_GAME_1:
                    draw(renderer, bonusGame1Texture, bonusGame);
                    if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT) {
                        SDL_GetMouseState(&x, &y);
                        if (isHit(x, y, Quit))
                        {
                            currentState = MENU;
                            break;
                        }
                        if (isHit(x, y, Rules)) {
                            currentState = RULES;
                            break;
                        }
                        if (isHit(x, y, Settings)) {
                            currentState = SETTINGS;
                            break;
                        }
                        if (isHit(x, y, three))
                        {
                            //это 1
                            currentState = BONUS_GAME_1_2;
                            break;
                        }
                        if (isHit(x, y, four))
                        {
                            //2
                            currentState = BONUS_GAME_1_2;
                            break;
                        }
                        if (isHit(x, y, five))
                        {
                            //3
                            currentState = BONUS_GAME_1_2;
                            break;
                        }
                        if (isHit(x, y, six))
                        {
                            //4
                            currentState = BONUS_GAME_1_2;
                            break;
                        }
                        if (isHit(x, y, seven))
                        {
                            //5
                            currentState = BONUS_GAME_1_2;
                            break;
                        }
                        if (isHit(x, y, eight))
                        {
                            //6
                            currentState = BONUS_GAME_1_2;
                            break;
                        }
                        
                    }
                    if (event.type == SDL_MOUSEMOTION) {
                        SDL_GetMouseState(&x, &y);
                        if (isHit(x, y, Quit)) {
                            draw(renderer, QuitTexture, Quit);
                            break;
                        }
                        if (isHit(x, y, Settings)) {
                            draw(renderer, NKTexture, Settings);
                            break;
                        }
                        if (isHit(x, y, Rules)) {
                            draw(renderer, RuleTexture, Rules);
                            break;
                        }
                        if (isHit(x, y, three))
                        {
                            //1
                            draw(renderer, redNumberTexture, three);
                            break;
                        }
                        if (isHit(x, y, four))
                        {
                            //2
                            draw(renderer, redNumberTexture, four);
                            break;
                        }
                        if (isHit(x, y, five))
                        {
                            //3
                            draw(renderer, redNumberTexture, five);
                            break;
                        }
                        if (isHit(x, y, six))
                        {
                            //4
                            draw(renderer, redNumberTexture, six);
                            break;
                        }
                        if (isHit(x, y, seven))
                        {
                            //5
                            draw(renderer, redNumberTexture, seven);
                            break;
                        }
                        if (isHit(x, y, eight))
                        {
                            //6
                            draw(renderer, redNumberTexture, eight);
                            break;
                        }
                    }
                    break;

                case BONUS_GAME_1_2:
                    draw(renderer, bonusGame1_2Texture, bonusGame);
                    if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT) {
                        SDL_GetMouseState(&x, &y);
                        if (isHit(x, y, Quit))
                        {
                            currentState = MENU;
                            break;
                        }
                        if (isHit(x, y, Rules)) {
                            currentState = RULES;
                            break;
                        }
                        if (isHit(x, y, Settings)) {
                            currentState = SETTINGS;
                            break;
                        }
                        if (isHit(x, y, three))
                        {
                            //1
                            currentState = BONUS_GAME_1_2;
                            draw(renderer, redNumberTexture, three);
                            break;
                        }
                        if (isHit(x, y, four))
                        {
                            //2
                            currentState = BONUS_GAME_1_2;
                            draw(renderer, redNumberTexture, four);
                            break;
                        }
                        if (isHit(x, y, five))
                        {
                            //3
                            currentState = BONUS_GAME_1_2;
                            draw(renderer, redNumberTexture, five);
                            break;
                        }
                        if (isHit(x, y, six))
                        {
                            //4
                            currentState = BONUS_GAME_1_2;
                            draw(renderer, redNumberTexture, six);
                            break;
                        }
                        if (isHit(x, y, seven))
                        {
                            //5
                            currentState = BONUS_GAME_1_2;
                            draw(renderer, redNumberTexture, seven);
                            break;
                        }
                        if (isHit(x, y, eight))
                        {
                            //6
                            currentState = BONUS_GAME_1_2;
                            draw(renderer, redNumberTexture, eight);
                            break;
                        }

                    }
                    if (event.type == SDL_MOUSEMOTION) {
                        SDL_GetMouseState(&x, &y);
                        if (isHit(x, y, Quit)) {
                            draw(renderer, QuitTexture, Quit);
                            break;
                        }
                        if (isHit(x, y, Settings)) {
                            draw(renderer, NKTexture, Settings);
                            break;
                        }
                        if (isHit(x, y, Rules)) {
                            draw(renderer, RuleTexture, Rules);
                            break;
                        }
                        if (isHit(x, y, three))
                        {
                            //1
                            draw(renderer, redNumberTexture, three);
                            break;
                        }
                        if (isHit(x, y, four))
                        {
                            //2
                            draw(renderer, redNumberTexture, four);

                            break;
                        }
                        if (isHit(x, y, five))
                        {
                            //3
                            draw(renderer, redNumberTexture, five);

                            break;
                        }
                        if (isHit(x, y, six))
                        {
                            //4
                            draw(renderer, redNumberTexture, six);
                            break;
                        }
                        if (isHit(x, y, seven))
                        {
                            //5
                            draw(renderer, redNumberTexture, seven);

                            break;
                        }
                        if (isHit(x, y, eight))
                        {
                            //6
                            draw(renderer, redNumberTexture, eight);
                            break;
                        }
                        
                    }
                    break;

                case BONUS_GAME_2:
                    draw(renderer, bonusGame2Texture, bonusGame);
                    if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT) {
                        SDL_GetMouseState(&x, &y);
                        if (isHit(x, y, Quit))
                        {
                            currentState = MENU;
                            break;
                        }
                        if (isHit(x, y, Rules)) {
                            currentState = RULES;
                            break;
                        }
                        if (isHit(x, y, Settings)) {
                            currentState = SETTINGS;
                            break;
                        }
                        if (isHit(x, y, three))
                        {
                            //2
                            currentState = BONUS_GAME_2_2;
                            draw(renderer, redNumberTexture, three);
                            break;
                        }
                        if (isHit(x, y, four))
                        {
                            //3
                            currentState = BONUS_GAME_2_2;
                            draw(renderer, redNumberTexture, four);
                            break;
                        }
                        if (isHit(x, y, five))
                        {
                            //4
                            currentState = BONUS_GAME_2_2;
                            draw(renderer, redNumberTexture, five);
                            break;
                        }
                        if (isHit(x, y, six))
                        {
                            //5
                            currentState = BONUS_GAME_2_2;
                            draw(renderer, redNumberTexture, six);
                            break;
                        }
                        if (isHit(x, y, seven))
                        {
                            //6
                            currentState = BONUS_GAME_2_2;
                            draw(renderer, redNumberTexture, seven);
                            break;
                        }
                        if (isHit(x, y, eight))
                        {
                            //7
                            currentState = BONUS_GAME_2_2;
                            draw(renderer, redNumberTexture, eight);
                            break;
                        }
                        if (isHit(x, y, nine))
                        {
                            //8
                            currentState = BONUS_GAME_2_2;
                            draw(renderer, redNumberTexture, nine);
                            break;
                        }
                        if (isHit(x, y, ten))
                        {
                            //9
                            currentState = BONUS_GAME_2_2;
                            draw(renderer, redNumberTexture, ten);
                            break;
                        }
                        if (isHit(x, y, eleven))
                        {
                            //10
                            currentState = BONUS_GAME_2_2;
                            draw(renderer, redNumberTexture, eleven);
                            break;
                        }
                        if (isHit(x, y, twelve))
                        {
                            //11
                            currentState = BONUS_GAME_2_2;
                            draw(renderer, redNumberTexture, twelve);
                            break;
                        }
                        if (isHit(x, y, thirteen))
                        {
                            //12
                            currentState = BONUS_GAME_2_2;
                            draw(renderer, redNumberTexture, thirteen);
                            break;
                        }
                        
                    }
                    if (event.type == SDL_MOUSEMOTION) {
                        SDL_GetMouseState(&x, &y);
                        if (isHit(x, y, Quit)) {
                            draw(renderer, QuitTexture, Quit);
                            break;
                        }
                        if (isHit(x, y, Settings)) {
                            draw(renderer, NKTexture, Settings);
                            break;
                        }
                        if (isHit(x, y, Rules)) {
                            draw(renderer, RuleTexture, Rules);
                            break;
                        }
                        if (isHit(x, y, three))
                        {
                            //2
                            draw(renderer, redNumberTexture, three);
                            break;
                        }
                        if (isHit(x, y, four))
                        {
                            //3
                            draw(renderer, redNumberTexture, four);
                            break;
                        }
                        if (isHit(x, y, five))
                        {
                            //4
                            draw(renderer, redNumberTexture, five);
                            break;
                        }
                        if (isHit(x, y, six))
                        {
                            //5
                            draw(renderer, redNumberTexture, six);
                            break;
                        }
                        if (isHit(x, y, seven))
                        {
                            //6
                            draw(renderer, redNumberTexture, seven);
                            break;
                        }
                        if (isHit(x, y, eight))
                        {
                            //7
                            draw(renderer, redNumberTexture, eight);
                            break;
                        }
                        if (isHit(x, y, nine))
                        {
                            //8
                            draw(renderer, redNumberTexture, nine);
                            break;
                        }
                        if (isHit(x, y, ten))
                        {
                            //9
                            draw(renderer, redNumberTexture, ten);
                            break;
                        }
                        if (isHit(x, y, eleven))
                        {
                            //10
                            draw(renderer, redNumberTexture, eleven);
                            break;
                        }
                        if (isHit(x, y, twelve))
                        {
                            //11
                            draw(renderer, redNumberTexture, twelve);
                            break;
                        }
                        if (isHit(x, y, thirteen))
                        {
                            //12
                            draw(renderer, redNumberTexture, thirteen);
                            break;
                        }
                    }
                    break;
                
                case BONUS_GAME_2_2:
                    draw(renderer, bonusGame2_2Texture, bonusGame);
                    if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT) {
                        SDL_GetMouseState(&x, &y);
                        if (isHit(x, y, Quit))
                        {
                            currentState = MENU;
                            break;
                        }
                        if (isHit(x, y, Rules)) {
                            currentState = RULES;
                            break;
                        }
                        if (isHit(x, y, Settings)) {
                            currentState = SETTINGS;
                            break;
                        }
                        if (isHit(x, y, three))
                        {
                            //2
                            currentState = BONUS_GAME_2_2;
                            draw(renderer, redNumberTexture, three);
                            break;
                        }
                        if (isHit(x, y, four))
                        {
                            //3
                            currentState = BONUS_GAME_2_2;
                            draw(renderer, redNumberTexture, four);
                            break;
                        }
                        if (isHit(x, y, five))
                        {
                            //4
                            currentState = BONUS_GAME_2_2;
                            draw(renderer, redNumberTexture, five);
                            break;
                        }
                        if (isHit(x, y, six))
                        {
                            //5
                            currentState = BONUS_GAME_2_2;
                            draw(renderer, redNumberTexture, six);
                            break;
                        }
                        if (isHit(x, y, seven))
                        {
                            //6
                            currentState = BONUS_GAME_2_2;
                            draw(renderer, redNumberTexture, seven);
                            break;
                        }
                        if (isHit(x, y, eight))
                        {
                            //7
                            currentState = BONUS_GAME_2_2;
                            draw(renderer, redNumberTexture, eight);
                            break;
                        }
                        if (isHit(x, y, nine))
                        {
                            //8
                            currentState = BONUS_GAME_2_2;
                            draw(renderer, redNumberTexture, nine);
                            break;
                        }
                        if (isHit(x, y, ten))
                        {
                            //9
                            currentState = BONUS_GAME_2_2;
                            draw(renderer, redNumberTexture, ten);
                            break;
                        }
                        if (isHit(x, y, eleven))
                        {
                            //10
                            currentState = BONUS_GAME_2_2;
                            draw(renderer, redNumberTexture, eleven);
                            break;
                        }
                        if (isHit(x, y, twelve))
                        {
                            //11
                            currentState = BONUS_GAME_2_2;
                            draw(renderer, redNumberTexture, twelve);
                            break;
                        }
                        if (isHit(x, y, thirteen))
                        {
                            //12
                            currentState = BONUS_GAME_2_2;
                            draw(renderer, redNumberTexture, thirteen);
                            break;
                        }

                    }
                    if (event.type == SDL_MOUSEMOTION) {
                        SDL_GetMouseState(&x, &y);
                        if (isHit(x, y, Quit)) {
                            draw(renderer, QuitTexture, Quit);
                            break;
                        }
                        if (isHit(x, y, Settings)) {
                            draw(renderer, NKTexture, Settings);
                            break;
                        }
                        if (isHit(x, y, Rules)) {
                            draw(renderer, RuleTexture, Rules);
                            break;
                        }
                        if (isHit(x, y, three))
                        {
                            //2
                            draw(renderer, redNumberTexture, three);
                            break;
                        }
                        if (isHit(x, y, four))
                        {
                            //3
                            draw(renderer, redNumberTexture, four);
                            break;
                        }
                        if (isHit(x, y, five))
                        {
                            //4
                            draw(renderer, redNumberTexture, five);
                            break;
                        }
                        if (isHit(x, y, six))
                        {
                            //5
                            draw(renderer, redNumberTexture, six);
                            break;
                        }
                        if (isHit(x, y, seven))
                        {
                            //6
                            draw(renderer, redNumberTexture, seven);
                            break;
                        }
                        if (isHit(x, y, eight))
                        {
                            //7
                            draw(renderer, redNumberTexture, eight);
                            break;
                        }
                        if (isHit(x, y, nine))
                        {
                            //8
                            draw(renderer, redNumberTexture, nine);
                            break;
                        }
                        if (isHit(x, y, ten))
                        {
                            //9
                            draw(renderer, redNumberTexture, ten);
                            break;
                        }
                        if (isHit(x, y, eleven))
                        {
                            //10
                            draw(renderer, redNumberTexture, eleven);
                            break;
                        }
                        if (isHit(x, y, twelve))
                        {
                            //11
                            draw(renderer, redNumberTexture, twelve);
                            break;
                        }
                        if (isHit(x, y, thirteen))
                        {
                            //12
                            draw(renderer, redNumberTexture, thirteen);
                            break;
                        }
                    }
                    break;

                case BONUS_GAME_3:
                    draw(renderer, bonusGame3Texture, bonusGame);
                    if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT) {
                        SDL_GetMouseState(&x, &y);
                        if (isHit(x, y, Quit))
                        {
                            currentState = MENU;
                            break;
                        }
                        if (isHit(x, y, Rules)) {
                            currentState = RULES;
                            break;
                        }
                        if (isHit(x, y, Settings)) {
                            currentState = SETTINGS;
                            break;
                        }
                        if (isHit(x, y, three))
                        {
                            //как написано вверху, так и есть 
                            currentState = BONUS_GAME_3_2;
                            break;
                        }
                        if (isHit(x, y, four))
                        {
                            currentState = BONUS_GAME_3_2;
                            break;
                        }
                        if (isHit(x, y, five))
                        {
                            currentState = BONUS_GAME_3_2;
                            break;
                        }
                        if (isHit(x, y, six))
                        {
                            currentState = BONUS_GAME_3_2;
                            break;
                        }
                        if (isHit(x, y, seven))
                        {
                            currentState = BONUS_GAME_3_2;
                            break;
                        }
                        if (isHit(x, y, eight))
                        {
                            currentState = BONUS_GAME_3_2;
                            break;
                        }
                        if (isHit(x, y, nine))
                        {
                            currentState = BONUS_GAME_3_2;
                            break;
                        }
                        if (isHit(x, y, ten))
                        {
                            currentState = BONUS_GAME_3_2;
                            break;
                        }
                        if (isHit(x, y, eleven))
                        {
                            currentState = BONUS_GAME_3_2;
                            break;
                        }
                        if (isHit(x, y, twelve))
                        {
                            currentState = BONUS_GAME_3_2;
                            break;
                        }
                        if (isHit(x, y, thirteen))
                        {
                            currentState = BONUS_GAME_3_2;
                            break;
                        }
                        if (isHit(x, y, fourteen))
                        {
                            currentState = BONUS_GAME_3_2;
                            break;
                        }
                        if (isHit(x, y, fifteen))
                        {
                            currentState = BONUS_GAME_3_2;
                            break;
                        }
                        if (isHit(x, y, sixteen))
                        {
                            currentState = BONUS_GAME_3_2;
                            break;
                        }
                        if (isHit(x, y, seventeen))
                        {
                            currentState = BONUS_GAME_3_2;
                            break;
                        }
                        if (isHit(x, y, eightteen))
                        {
                            currentState = BONUS_GAME_3_2;
                            break;
                        }
                    }
                    if (event.type == SDL_MOUSEMOTION) {
                        SDL_GetMouseState(&x, &y);
                        if (isHit(x, y, Quit)) {
                            draw(renderer, QuitTexture, Quit);
                            break;
                        }
                        if (isHit(x, y, Settings)) {
                            draw(renderer, NKTexture, Settings);
                            break;
                        }
                        if (isHit(x, y, Rules)) {
                            draw(renderer, RuleTexture, Rules);
                            break;
                        }
                        if (isHit(x, y, three))
                        {
                            draw(renderer, redNumberTexture, three);
                            break;
                        }
                        if (isHit(x, y, four))
                        {
                            draw(renderer, redNumberTexture, four);
                            break;
                        }
                        if (isHit(x, y, five))
                        {
                            draw(renderer, redNumberTexture, five);
                            break;
                        }
                        if (isHit(x, y, six))
                        {
                            draw(renderer, redNumberTexture, six);
                            break;
                        }
                        if (isHit(x, y, seven))
                        {
                            draw(renderer, redNumberTexture, seven);
                            break;
                        }
                        if (isHit(x, y, eight))
                        {
                            draw(renderer, redNumberTexture, eight);
                            break;
                        }
                        if (isHit(x, y, nine))
                        {
                            draw(renderer, redNumberTexture, nine);
                            break;
                        }
                        if (isHit(x, y, ten))
                        {
                            draw(renderer, redNumberTexture, ten);
                            break;
                        }
                        if (isHit(x, y, eleven))
                        {
                            draw(renderer, redNumberTexture, eleven);
                            break;
                        }
                        if (isHit(x, y, twelve))
                        {
                            draw(renderer, redNumberTexture, twelve);
                            break;
                        }
                        if (isHit(x, y, thirteen))
                        {
                            draw(renderer, redNumberTexture, thirteen);
                            break;
                        }
                        if (isHit(x, y, fourteen))
                        {
                            draw(renderer, redNumberTexture, fourteen);
                            break;
                        }
                        if (isHit(x, y, fifteen))
                        {
                            draw(renderer, redNumberTexture, fifteen);
                            break;
                        }
                        if (isHit(x, y, sixteen))
                        {
                            draw(renderer, redNumberTexture, sixteen);
                            break;
                        }
                        if (isHit(x, y, seventeen))
                        {
                            draw(renderer, redNumberTexture, seventeen);
                            break;
                        }
                        if (isHit(x, y, eightteen))
                        {
                            draw(renderer, redNumberTexture, eightteen);
                            break;
                        }
                    }
                    break;

                case BONUS_GAME_3_2:
                    draw(renderer, bonusGame3_2Texture, bonusGame);
                    if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT) {
                        SDL_GetMouseState(&x, &y);
                        if (isHit(x, y, Quit))
                        {
                            currentState = MENU;
                            break;
                        }
                        if (isHit(x, y, Rules)) {
                            currentState = RULES;
                            break;
                        }
                        if (isHit(x, y, Settings)) {
                            currentState = SETTINGS;
                            break;
                        }
                        if (isHit(x, y, three))
                        {
                            //как написано вверху, так и есть 
                            currentState = BONUS_GAME_3_2;
                            break;
                        }
                        if (isHit(x, y, four))
                        {
                            currentState = BONUS_GAME_3_2;
                            break;
                        }
                        if (isHit(x, y, five))
                        {
                            currentState = BONUS_GAME_3_2;
                            break;
                        }
                        if (isHit(x, y, six))
                        {
                            currentState = BONUS_GAME_3_2;
                            break;
                        }
                        if (isHit(x, y, seven))
                        {
                            currentState = BONUS_GAME_3_2;
                            break;
                        }
                        if (isHit(x, y, eight))
                        {
                            currentState = BONUS_GAME_3_2;
                            break;
                        }
                        if (isHit(x, y, nine))
                        {
                            currentState = BONUS_GAME_3_2;
                            break;
                        }
                        if (isHit(x, y, ten))
                        {
                            currentState = BONUS_GAME_3_2;
                            break;
                        }
                        if (isHit(x, y, eleven))
                        {
                            currentState = BONUS_GAME_3_2;
                            break;
                        }
                        if (isHit(x, y, twelve))
                        {
                            currentState = BONUS_GAME_3_2;
                            break;
                        }
                        if (isHit(x, y, thirteen))
                        {
                            currentState = BONUS_GAME_3_2;
                            break;
                        }
                        if (isHit(x, y, fourteen))
                        {
                            currentState = BONUS_GAME_3_2;
                            break;
                        }
                        if (isHit(x, y, fifteen))
                        {
                            currentState = BONUS_GAME_3_2;
                            break;
                        }
                        if (isHit(x, y, sixteen))
                        {
                            currentState = BONUS_GAME_3_2;
                            break;
                        }
                        if (isHit(x, y, seventeen))
                        {
                            currentState = BONUS_GAME_3_2;
                            break;
                        }
                        if (isHit(x, y, eightteen))
                        {
                            currentState = BONUS_GAME_3_2;
                            break;
                        }
                    }
                    if (event.type == SDL_MOUSEMOTION) {
                        SDL_GetMouseState(&x, &y);
                        if (isHit(x, y, Quit)) {
                            draw(renderer, QuitTexture, Quit);
                            break;
                        }
                        if (isHit(x, y, Settings)) {
                            draw(renderer, NKTexture, Settings);
                            break;
                        }
                        if (isHit(x, y, Rules)) {
                            draw(renderer, RuleTexture, Rules);
                            break;
                        }
                        if (isHit(x, y, three))
                        {
                            draw(renderer, redNumberTexture, three);
                            break;
                        }
                        if (isHit(x, y, four))
                        {
                            draw(renderer, redNumberTexture, four);
                            break;
                        }
                        if (isHit(x, y, five))
                        {
                            draw(renderer, redNumberTexture, five);
                            break;
                        }
                        if (isHit(x, y, six))
                        {
                            draw(renderer, redNumberTexture, six);
                            break;
                        }
                        if (isHit(x, y, seven))
                        {
                            draw(renderer, redNumberTexture, seven);
                            break;
                        }
                        if (isHit(x, y, eight))
                        {
                            draw(renderer, redNumberTexture, eight);
                            break;
                        }
                        if (isHit(x, y, nine))
                        {
                            draw(renderer, redNumberTexture, nine);
                            break;
                        }
                        if (isHit(x, y, ten))
                        {
                            draw(renderer, redNumberTexture, ten);
                            break;
                        }
                        if (isHit(x, y, eleven))
                        {
                            draw(renderer, redNumberTexture, eleven);
                            break;
                        }
                        if (isHit(x, y, twelve))
                        {
                            draw(renderer, redNumberTexture, twelve);
                            break;
                        }
                        if (isHit(x, y, thirteen))
                        {
                            draw(renderer, redNumberTexture, thirteen);
                            break;
                        }
                        if (isHit(x, y, fourteen))
                        {
                            draw(renderer, redNumberTexture, fourteen);
                            break;
                        }
                        if (isHit(x, y, fifteen))
                        {
                            draw(renderer, redNumberTexture, fifteen);
                            break;
                        }
                        if (isHit(x, y, sixteen))
                        {
                            draw(renderer, redNumberTexture, sixteen);
                            break;
                        }
                        if (isHit(x, y, seventeen))
                        {
                            draw(renderer, redNumberTexture, seventeen);
                            break;
                        }
                        if (isHit(x, y, eightteen))
                        {
                            draw(renderer, redNumberTexture, eightteen);
                            break;
                        }
                    }
                    break;

                //Дописать переход из 2-х(вторых) попыток в следующие состояния, надо будет сделать функцию для рандома, чтобы понять
                //угадал ли человек выбранное им число, в фунцию будем передавать нынешнее состояние и выбранное число 
                //пусть фунция будет булева, если угадывает, то состояние поменяется на картинку с "вы угадали", если нет, то нет

                case MAIN_GAME:
                    break;

            }
        }
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
        //SDL_RenderClear(renderer);
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
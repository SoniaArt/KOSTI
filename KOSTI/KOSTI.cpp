#include "SDL.h"
#include "stdlib.h"
#include <SDL_ttf.h>
#include "SDL_image.h"
#include "ctime"
#include "SDL_mixer.h"
#include <stdio.h>
#include <locale.h>
#include <windows.h>
#pragma comment(lib, "SDL2_mixer.lib")
Mix_Chunk* Sound = NULL;
Mix_Music* fon = NULL;
void loadmusic()
{
    fon = Mix_LoadMUS("fon.wav");
    Mix_PlayMusic(fon, -1);
}
void sound(char* name)
{
    Sound = Mix_LoadWAV(name);
    Mix_PlayChannel(-1, Sound, 0);
}

enum State {
    MENU,
    GAME,
    CHOICE_GAME_MODE,
    CHOICE_DIFFICULTY_LEVEL,
    CHOICE_BONUS_GAME,
    CHOICE_PLAYER1,
    CHOICE_PLAYER2,
    BONUS_GAME,
    BONUS_GAME_1,
    BONUS_GAME_1_2,
    BONUS_GAME_2,
    BONUS_GAME_2_2,
    BONUS_GAME_3,
    BONUS_GAME_3_2,
    BONUS_WIN,
    BONUS_LOSE,
    MAIN_GAME,
    EXIT,
    SETTINGS,
    RULES,
    RULES_2,
    PROGRESS,
};
SDL_Texture* get_text_texture(SDL_Renderer*& renderer, char* text, TTF_Font* font) {
    SDL_Surface* textSurface = NULL;
    SDL_Color fore_color = { 255,255, 255 };
    textSurface = TTF_RenderUTF8_Blended(font, text, fore_color);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, textSurface);
    SDL_FreeSurface(textSurface);
    return texture;
}
void draw_text(SDL_Renderer*& renderer, SDL_Texture* texture, SDL_Rect rect)
{
    SDL_RenderCopy(renderer, texture, NULL, &rect);
}
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
    srand(time(NULL));
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;
    window = SDL_CreateWindow(u8"Кости", 0, 30, 1535, 800, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, 0);

    TTF_Init();
    TTF_Font* my_font = TTF_OpenFont("shrift.ttf", 36);
    SDL_Texture* textTexture;
    int k = 0;
    char text[10];

    /*Mix_Init(0);
    Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 1024);

    char music[10] = "music.wav";*/

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

    SDL_Surface* bonusWinImage = IMG_Load("bonusWin.bmp"); //победа в бонусной игре
    SDL_SetColorKey(bonusWinImage, SDL_TRUE, SDL_MapRGB(bonusWinImage->format, 255, 255, 255));
    SDL_Texture* bonusWinTexture = SDL_CreateTextureFromSurface(renderer, bonusWinImage);
    SDL_FreeSurface(bonusWinImage);


    SDL_Surface* bonusLoseImage = IMG_Load("bonusLose.bmp"); //проигрыш в бонусной игре
    SDL_SetColorKey(bonusLoseImage, SDL_TRUE, SDL_MapRGB(bonusLoseImage->format, 255, 255, 255));
    SDL_Texture* bonusLoseTexture = SDL_CreateTextureFromSurface(renderer, bonusLoseImage);
    SDL_FreeSurface(bonusLoseImage);

    SDL_Surface* point1Image = IMG_Load("point1.bmp"); //кубик со значением 1
    SDL_SetColorKey(point1Image, SDL_TRUE, SDL_MapRGB(point1Image->format, 255, 255, 255));
    SDL_Texture* point1Texture = SDL_CreateTextureFromSurface(renderer, point1Image);
    SDL_FreeSurface(point1Image);

    SDL_Surface* point2Image = IMG_Load("point2.bmp"); //кубик со значением 2
    SDL_SetColorKey(point2Image, SDL_TRUE, SDL_MapRGB(point2Image->format, 255, 255, 255));
    SDL_Texture* point2Texture = SDL_CreateTextureFromSurface(renderer, point2Image);
    SDL_FreeSurface(point2Image);

    SDL_Surface* point3Image = IMG_Load("point3.bmp"); //кубик со значением 3
    SDL_SetColorKey(point3Image, SDL_TRUE, SDL_MapRGB(point3Image->format, 255, 255, 255));
    SDL_Texture* point3Texture = SDL_CreateTextureFromSurface(renderer, point3Image);
    SDL_FreeSurface(point3Image);

    SDL_Surface* point4Image = IMG_Load("point4.bmp"); //кубик со значением 4
    SDL_SetColorKey(point4Image, SDL_TRUE, SDL_MapRGB(point4Image->format, 255, 255, 255));
    SDL_Texture* point4Texture = SDL_CreateTextureFromSurface(renderer, point4Image);
    SDL_FreeSurface(point4Image);

    SDL_Surface* point5Image = IMG_Load("point5.bmp"); //кубик со значением 5
    SDL_SetColorKey(point5Image, SDL_TRUE, SDL_MapRGB(point5Image->format, 255, 255, 255));
    SDL_Texture* point5Texture = SDL_CreateTextureFromSurface(renderer, point5Image);
    SDL_FreeSurface(point5Image);

    SDL_Surface* point6Image = IMG_Load("point6.bmp"); //кубик со значением 6
    SDL_SetColorKey(point6Image, SDL_TRUE, SDL_MapRGB(point6Image->format, 255, 255, 255));
    SDL_Texture* point6Texture = SDL_CreateTextureFromSurface(renderer, point6Image);
    SDL_FreeSurface(point6Image);

    SDL_Surface* settingsImage = IMG_Load("settings.bmp"); //окно настроек
    SDL_SetColorKey(settingsImage, SDL_TRUE, SDL_MapRGB(settingsImage->format, 255, 255, 255));
    SDL_Texture* settingsTexture = SDL_CreateTextureFromSurface(renderer, settingsImage);
    SDL_FreeSurface(settingsImage);

    SDL_Surface* onImage = IMG_Load("on.bmp"); //настройка включена
    SDL_SetColorKey(onImage, SDL_TRUE, SDL_MapRGB(onImage->format, 255, 255, 255));
    SDL_Texture* onTexture = SDL_CreateTextureFromSurface(renderer, onImage);
    SDL_FreeSurface(onImage);

    SDL_Surface* offImage = IMG_Load("off.bmp"); //настройка выключена
    SDL_SetColorKey(offImage, SDL_TRUE, SDL_MapRGB(offImage->format, 255, 255, 255));
    SDL_Texture* offTexture = SDL_CreateTextureFromSurface(renderer, offImage);
    SDL_FreeSurface(offImage);

    SDL_Surface* choicePlayer1Image = IMG_Load("choicePlayer1.bmp"); //окно выбора первого игрока
    SDL_SetColorKey(choicePlayer1Image, SDL_TRUE, SDL_MapRGB(choicePlayer1Image->format, 255, 255, 255));
    SDL_Texture* choicePlayer1Texture = SDL_CreateTextureFromSurface(renderer, choicePlayer1Image);
    SDL_FreeSurface(choicePlayer1Image);

    SDL_Surface* choicePlayer2Image = IMG_Load("choicePlayer2.bmp"); //окно выбора второго игрока
    SDL_SetColorKey(choicePlayer2Image, SDL_TRUE, SDL_MapRGB(choicePlayer2Image->format, 255, 255, 255));
    SDL_Texture* choicePlayer2Texture = SDL_CreateTextureFromSurface(renderer, choicePlayer2Image);
    SDL_FreeSurface(choicePlayer2Image);

    SDL_Surface* welcomeMainGameImage = IMG_Load("welcomeMainGame.bmp"); //окно выбора второго игрока
    SDL_SetColorKey(welcomeMainGameImage, SDL_TRUE, SDL_MapRGB(welcomeMainGameImage->format, 255, 255, 255));
    SDL_Texture* welcomeMainGameTexture = SDL_CreateTextureFromSurface(renderer, welcomeMainGameImage);
    SDL_FreeSurface(welcomeMainGameImage);

    SDL_Surface* mainGameImage = IMG_Load("mainGame.bmp"); //окно выбора второго игрока
    SDL_SetColorKey(mainGameImage, SDL_TRUE, SDL_MapRGB(mainGameImage->format, 255, 255, 255));
    SDL_Texture* mainGameTexture = SDL_CreateTextureFromSurface(renderer, mainGameImage);
    SDL_FreeSurface(mainGameImage);

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
    SDL_Rect easy = { 59, 229, 310,460 };
    SDL_Rect medium = { 422, 229, 310, 460 };
    SDL_Rect hard = { 784, 229, 310,460 };
    SDL_Rect veryHard = { 1144, 229, 310, 460 };

    SDL_Rect choiceBonusGame = { 0, 0, 1535, 800 };
    SDL_Rect yes = { 298, 315, 939,  100 };
    SDL_Rect no = { 298, 477, 939, 100 };


    SDL_Rect bonusGame = { 0, 0, 1535, 800 };
    SDL_Rect oneCube = { 594, 252, 60, 60 };
    SDL_Rect twoCube = { 728, 252, 60, 60 };
    SDL_Rect threeCube = { 862, 252, 60, 60 };


    SDL_Rect three = { 10, 431, 85, 60 };
    SDL_Rect four = { 105, 431, 85, 60 };
    SDL_Rect five = { 200, 431, 85, 60 };
    SDL_Rect six = { 295, 431, 85, 60 };
    SDL_Rect seven = { 390, 431, 85, 60 };
    SDL_Rect eight = { 485, 431, 85, 60 };
    SDL_Rect nine = { 580, 431, 85, 60 };
    SDL_Rect ten = { 675, 431, 85, 60 };
    SDL_Rect eleven = { 770, 431, 85, 60 };
    SDL_Rect twelve = { 865, 431, 85, 60 };
    SDL_Rect thirteen = { 960, 431, 85, 60 };
    SDL_Rect fourteen = { 1055, 431, 85, 60 };
    SDL_Rect fifteen = { 1150, 431, 85, 60 };
    SDL_Rect sixteen = { 1245, 431, 85, 60 };
    SDL_Rect seventeen = { 1340, 431, 85, 60 };
    SDL_Rect eightteen = { 1435, 431, 85, 60 };

    SDL_Rect bonus_score = { 848, 423, 70, 70 };
    SDL_Rect kub1 = { 590,268,100,100 };
    SDL_Rect kub2 = { 714, 268, 100, 100 };
    SDL_Rect kub3 = { 838,268,100,100 };

    SDL_Rect onFonMusic = { 28,411,717,100 };
    SDL_Rect offFonMusic = { 28,536,717,100 };

    SDL_Rect onMusEffects = { 790,406,717,100 };
    SDL_Rect offMusEffects = { 790,531,717,100 };



    SDL_Event event;
    State currentState = MENU;
    bool quit = false;

    int x, y;

    int choiceMode = 0;
    int choiceDiffLevel = 0;

    int try1 = 0, try2 = 0;
    int k1 = 0, k2[2] = { 0 }, k3[3] = { 0 };

    int choice_k = 0;
    int sum2 = 0;

    int fonMusic = 1;
    int musEffects = 1;

    int players = 0;
    int player = 1;

    Mix_Init(0);
    Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 1024);
    if (fonMusic == 1) { loadmusic(); }
    char music[10] = "music.wav";
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
                    if (isHit(x, y, Rules) || isHit(x, y, Settings) || isHit(x, y, startGame)) {
                        if (musEffects == 1) { sound(music); }
                    }
                    if (isHit(x, y, Quit))
                    {
                        quit = true;
                    }
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
            case SETTINGS:
                draw(renderer, settingsTexture, bonusGame);
                if (fonMusic == 1) { draw(renderer, onTexture, onFonMusic); }
                else if (fonMusic == 0) { draw(renderer, offTexture, offFonMusic); }
                if (musEffects == 1) { draw(renderer, onTexture, onMusEffects); }
                else if (musEffects == 0) { draw(renderer, offTexture, offMusEffects); }
                if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT) {
                    SDL_GetMouseState(&x, &y);
                    if (isHit(x, y, Rules) || isHit(x, y, Quit) || isHit(x, y, onFonMusic) || isHit(x, y, offFonMusic) || isHit(x, y, onMusEffects) || isHit(x, y, offMusEffects)) {
                        if (musEffects == 1) { sound(music); }
                    }
                    if (isHit(x, y, Quit)) {
                        currentState = MENU;
                        break;
                    }
                    if (isHit(x, y, Rules)) {
                        currentState = RULES;
                        break;
                    }
                    if (isHit(x, y, onFonMusic)) {
                        fonMusic = 1;
                        if (fonMusic == 1) { loadmusic(); }
                        currentState = SETTINGS;
                        break;
                    }
                    if (isHit(x, y, offFonMusic)) {
                        fonMusic = 0;
                        Mix_HaltMusic();
                        currentState = SETTINGS;
                        break;
                    }
                    if (isHit(x, y, onMusEffects)) {
                        musEffects = 1;
                        currentState = SETTINGS;
                        break;
                    }
                    if (isHit(x, y, offMusEffects)) {
                        musEffects = 0;
                        currentState = SETTINGS;
                        break;
                    }
                }
                if (event.type == SDL_MOUSEMOTION) {
                    SDL_GetMouseState(&x, &y);
                    if (isHit(x, y, Quit)) {
                        draw(renderer, QuitTexture, Quit);
                        break;
                    }
                    if (isHit(x, y, Rules)) {
                        draw(renderer, RuleTexture, Rules);
                        break;
                    }
                }
                break;
            case RULES:
                SDL_RenderCopy(renderer, R1Texture, NULL, NULL);
                if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT) {
                    SDL_GetMouseState(&x, &y);
                    if (isHit(x, y, rightArrow) || isHit(x, y, Settings) || isHit(x, y, Quit)) {
                        if (musEffects == 1) { sound(music); }
                    }
                    if (isHit(x, y, Quit))
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
                    if (isHit(x, y, leftArrow) || isHit(x, y, Settings) || isHit(x, y, Quit)) {
                        if (musEffects == 1) { sound(music); }
                    }
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
                    if (isHit(x, y, Quit) || isHit(x, y, Settings) || isHit(x, y, Rules) || isHit(x, y, playerPlayer) || isHit(x, y, playerComp)) {
                        if (musEffects == 1) { sound(music); }
                    }
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
                        players = 2;
                        currentState = CHOICE_DIFFICULTY_LEVEL;
                        break;
                    }
                    if (isHit(x, y, playerComp)) {
                        players = 1;
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
                    if (isHit(x, y, Quit) || isHit(x, y, Settings) || isHit(x, y, Rules) || isHit(x, y, easy) || isHit(x, y, medium) || isHit(x, y, hard) || isHit(x, y, veryHard)) {
                        if (musEffects == 1) { sound(music); }
                    }
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
                        choiceDiffLevel = 1;
                        if (players == 1) {
                            currentState = CHOICE_BONUS_GAME;
                        }
                        else if (players == 2) {
                            currentState = CHOICE_PLAYER1;
                        }
                        break;
                    }
                    if (isHit(x, y, medium)) {
                        choiceDiffLevel = 2;
                        if (players == 1) {
                            currentState = CHOICE_BONUS_GAME;
                        }
                        else if (players == 2) {
                            currentState = CHOICE_PLAYER1;
                        }
                        break;
                    }
                    if (isHit(x, y, hard)) {
                        choiceDiffLevel = 3;
                        if (players == 1) {
                            currentState = CHOICE_BONUS_GAME;
                        }
                        else if (players == 2) {
                            currentState = CHOICE_PLAYER1;
                        }
                        break;
                    }
                    if (isHit(x, y, veryHard)) {
                        choiceDiffLevel = 4;
                        if (players == 1) {
                            currentState = CHOICE_BONUS_GAME;
                        }
                        else if (players == 2) {
                            currentState = CHOICE_PLAYER1;
                        }
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
            case CHOICE_PLAYER1:
                draw(renderer, choicePlayer1Texture, bonusGame);
                if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT) {
                    currentState = CHOICE_BONUS_GAME;
                }
                break;
            case CHOICE_PLAYER2:
                draw(renderer, choicePlayer2Texture, bonusGame);
                SDL_RenderPresent(renderer);
                if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT) {
                    currentState = CHOICE_BONUS_GAME;
                }
                break;
            case CHOICE_BONUS_GAME:
                draw(renderer, choiceBonusGameTexture, choiceBonusGame);
                if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT) {
                    SDL_GetMouseState(&x, &y);
                    if (isHit(x, y, Quit) || isHit(x, y, Settings) || isHit(x, y, Rules) || isHit(x, y, yes) || isHit(x, y, no)) {
                        if (musEffects == 1) { sound(music); }
                    }
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
                        if (players == 1) {
                            currentState = MAIN_GAME;
                        }
                        if (players == 2) {
                            if (player == 1) { player = 2; currentState = CHOICE_PLAYER2; break; }
                            if (player == 2) {
                                draw(renderer, welcomeMainGameTexture, bonusGame);
                                SDL_RenderPresent(renderer);
                                SDL_Delay(2000);
                                currentState = MAIN_GAME;
                                break;
                            }
                        }

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
                    if (isHit(x, y, Quit) || isHit(x, y, Rules) || isHit(x, y, Settings) || isHit(x, y, oneCube) || isHit(x, y, twoCube) || isHit(x, y, threeCube)) {
                        if (musEffects == 1) { sound(music); }
                    }
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
                        choice_k = 1;
                        currentState = BONUS_GAME_1;
                        break;
                    }
                    if (isHit(x, y, twoCube)) {
                        choice_k = 2;
                        currentState = BONUS_GAME_2;
                        break;
                    }
                    if (isHit(x, y, threeCube)) {
                        choice_k = 3;
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
                    if (isHit(x, y, Quit) || isHit(x, y, Rules) || isHit(x, y, Settings) || isHit(x, y, three) || isHit(x, y, four) || isHit(x, y, five) ||
                        isHit(x, y, six) || isHit(x, y, seven) || isHit(x, y, eight)) {
                        if (musEffects == 1) { sound(music); }
                    }
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
                        try1 = 1;
                        currentState = BONUS_GAME_1_2;
                        break;
                    }
                    if (isHit(x, y, four))
                    {
                        //2
                        try1 = 2;
                        currentState = BONUS_GAME_1_2;
                        break;
                    }
                    if (isHit(x, y, five))
                    {
                        //3
                        try1 = 3;
                        currentState = BONUS_GAME_1_2;
                        break;
                    }
                    if (isHit(x, y, six))
                    {
                        //4
                        try1 = 4;
                        currentState = BONUS_GAME_1_2;
                        break;
                    }
                    if (isHit(x, y, seven))
                    {
                        //5
                        try1 = 5;
                        currentState = BONUS_GAME_1_2;
                        break;
                    }
                    if (isHit(x, y, eight))
                    {
                        //6
                        try1 = 6;
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
                    if (isHit(x, y, Quit) || isHit(x, y, Rules) || isHit(x, y, Settings) || isHit(x, y, three) || isHit(x, y, four) || isHit(x, y, five) ||
                        isHit(x, y, six) || isHit(x, y, seven) || isHit(x, y, eight)) {
                        if (musEffects == 1) { sound(music); }
                    }
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
                        try2 = 1;
                        k1 = rand() % 6 + 1;
                        if (try1 == k1 || try2 == k1)
                        {
                            currentState = BONUS_WIN;
                        }
                        else { currentState = BONUS_LOSE; }

                        //draw(renderer, redNumberTexture, three);
                        break;
                    }
                    if (isHit(x, y, four))
                    {
                        //2
                        try2 = 2;
                        k1 = rand() % 6 + 1;
                        if (try1 == k1 || try2 == k1)
                        {
                            currentState = BONUS_WIN;
                        }
                        else { currentState = BONUS_LOSE; }

                        //draw(renderer, redNumberTexture, four);
                        break;
                    }
                    if (isHit(x, y, five))
                    {
                        //3
                        try2 = 3;
                        k1 = rand() % 6 + 1;
                        if (try1 == k1 || try2 == k1)
                        {
                            currentState = BONUS_WIN;
                        }
                        else { currentState = BONUS_LOSE; }

                        //draw(renderer, redNumberTexture, five);
                        break;
                    }
                    if (isHit(x, y, six))
                    {
                        //4
                        try2 = 4;
                        k1 = rand() % 6 + 1;
                        if (try1 == k1 || try2 == k1)
                        {
                            currentState = BONUS_WIN;
                        }
                        else { currentState = BONUS_LOSE; }
                        //draw(renderer, redNumberTexture, six);
                        break;
                    }
                    if (isHit(x, y, seven))
                    {
                        //5
                        try2 = 5;
                        k1 = rand() % 6 + 1;
                        if (try1 == k1 || try2 == k1)
                        {
                            currentState = BONUS_WIN;
                        }
                        else { currentState = BONUS_LOSE; }
                        //draw(renderer, redNumberTexture, seven);
                        break;
                    }
                    if (isHit(x, y, eight))
                    {
                        //6
                        try2 = 6;
                        k1 = rand() % 6 + 1;
                        if (try1 == k1 || try2 == k1)
                        {
                            currentState = BONUS_WIN;
                        }
                        else { currentState = BONUS_LOSE; }
                        //draw(renderer, redNumberTexture, eight);
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
                    if (isHit(x, y, Quit) || isHit(x, y, Rules) || isHit(x, y, Settings) || isHit(x, y, three) || isHit(x, y, four) || isHit(x, y, five) ||
                        isHit(x, y, six) || isHit(x, y, seven) || isHit(x, y, eight) || isHit(x, y, nine) || isHit(x, y, ten) || isHit(x, y, eleven) ||
                        isHit(x, y, twelve) || isHit(x, y, thirteen)) {
                        if (musEffects == 1) { sound(music); }
                    }
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
                        try1 = 2;
                        currentState = BONUS_GAME_2_2;
                        break;
                    }
                    if (isHit(x, y, four))
                    {
                        //3
                        try1 = 3;
                        currentState = BONUS_GAME_2_2;
                        break;
                    }
                    if (isHit(x, y, five))
                    {
                        //4
                        try1 = 4;
                        currentState = BONUS_GAME_2_2;
                        break;
                    }
                    if (isHit(x, y, six))
                    {
                        //5
                        try1 = 5;
                        currentState = BONUS_GAME_2_2;
                        break;
                    }
                    if (isHit(x, y, seven))
                    {
                        //6
                        try1 = 6;
                        currentState = BONUS_GAME_2_2;
                        break;
                    }
                    if (isHit(x, y, eight))
                    {
                        //7
                        try1 = 7;
                        currentState = BONUS_GAME_2_2;
                        break;
                    }
                    if (isHit(x, y, nine))
                    {
                        //8
                        try1 = 8;
                        currentState = BONUS_GAME_2_2;
                        break;
                    }
                    if (isHit(x, y, ten))
                    {
                        //9
                        try1 = 9;
                        currentState = BONUS_GAME_2_2;
                        break;
                    }
                    if (isHit(x, y, eleven))
                    {
                        //10
                        try1 = 10;
                        currentState = BONUS_GAME_2_2;
                        break;
                    }
                    if (isHit(x, y, twelve))
                    {
                        //11
                        try1 = 11;
                        currentState = BONUS_GAME_2_2;
                        break;
                    }
                    if (isHit(x, y, thirteen))
                    {
                        //12
                        try1 = 12;
                        currentState = BONUS_GAME_2_2;
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
                    if (isHit(x, y, Quit) || isHit(x, y, Rules) || isHit(x, y, Settings) || isHit(x, y, three) || isHit(x, y, four) || isHit(x, y, five) ||
                        isHit(x, y, six) || isHit(x, y, seven) || isHit(x, y, eight) || isHit(x, y, nine) || isHit(x, y, ten) || isHit(x, y, eleven) ||
                        isHit(x, y, twelve) || isHit(x, y, thirteen)) {
                        if (musEffects == 1) { sound(music); }
                    }
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
                        try2 = 2;
                        sum2 = 0;
                        for (int i = 0; i < 2; i++) {
                            k2[i] = rand() % 6 + 1;
                            sum2 += k2[i];
                        }
                        if (sum2 == try1 || sum2 == try2) { currentState = BONUS_WIN; }
                        else { currentState = BONUS_LOSE; }
                        break;
                    }
                    if (isHit(x, y, four))
                    {
                        //3
                        try2 = 3;
                        sum2 = 0;
                        for (int i = 0; i < 2; i++) {
                            k2[i] = rand() % 6 + 1;
                            sum2 += k2[i];
                        }
                        if (sum2 == try1 || sum2 == try2) { currentState = BONUS_WIN; }
                        else { currentState = BONUS_LOSE; }
                        break;
                    }
                    if (isHit(x, y, five))
                    {
                        //4
                        try2 = 4;
                        sum2 = 0;
                        for (int i = 0; i < 2; i++) {
                            k2[i] = rand() % 6 + 1;
                            sum2 += k2[i];
                        }
                        if (sum2 == try1 || sum2 == try2) { currentState = BONUS_WIN; }
                        else { currentState = BONUS_LOSE; }
                        break;
                    }
                    if (isHit(x, y, six))
                    {
                        //5
                        try2 = 5;
                        int sum2 = 0;
                        for (int i = 0; i < 2; i++) {
                            k2[i] = rand() % 6 + 1;
                            sum2 += k2[i];
                        }
                        if (sum2 == try1 || sum2 == try2) { currentState = BONUS_WIN; }
                        else { currentState = BONUS_LOSE; }
                        break;
                    }
                    if (isHit(x, y, seven))
                    {
                        //6
                        try2 = 6;
                        sum2 = 0;
                        for (int i = 0; i < 2; i++) {
                            k2[i] = rand() % 6 + 1;
                            sum2 += k2[i];
                        }
                        if (sum2 == try1 || sum2 == try2) { currentState = BONUS_WIN; }
                        else { currentState = BONUS_LOSE; }
                        break;
                    }
                    if (isHit(x, y, eight))
                    {
                        //7
                        try2 = 7;
                        sum2 = 0;
                        for (int i = 0; i < 2; i++) {
                            k2[i] = rand() % 6 + 1;
                            sum2 += k2[i];
                        }
                        if (sum2 == try1 || sum2 == try2) { currentState = BONUS_WIN; }
                        else { currentState = BONUS_LOSE; }
                        break;
                    }
                    if (isHit(x, y, nine))
                    {
                        //8
                        try2 = 8;
                        sum2 = 0;
                        for (int i = 0; i < 2; i++) {
                            k2[i] = rand() % 6 + 1;
                            sum2 += k2[i];
                        }
                        if (sum2 == try1 || sum2 == try2) { currentState = BONUS_WIN; }
                        else { currentState = BONUS_LOSE; }
                        break;
                    }
                    if (isHit(x, y, ten))
                    {
                        //9
                        try2 = 9;
                        sum2 = 0;
                        for (int i = 0; i < 2; i++) {
                            k2[i] = rand() % 6 + 1;
                            sum2 += k2[i];
                        }
                        if (sum2 == try1 || sum2 == try2) { currentState = BONUS_WIN; }
                        else { currentState = BONUS_LOSE; }
                        break;
                    }
                    if (isHit(x, y, eleven))
                    {
                        //10
                        try2 = 10;
                        sum2 = 0;
                        for (int i = 0; i < 2; i++) {
                            k2[i] = rand() % 6 + 1;
                            sum2 += k2[i];
                        }
                        if (sum2 == try1 || sum2 == try2) { currentState = BONUS_WIN; }
                        else { currentState = BONUS_LOSE; }
                        break;
                    }
                    if (isHit(x, y, twelve))
                    {
                        //11
                        try2 = 11;
                        sum2 = 0;
                        for (int i = 0; i < 2; i++) {
                            k2[i] = rand() % 6 + 1;
                            sum2 += k2[i];
                        }
                        if (sum2 == try1 || sum2 == try2) { currentState = BONUS_WIN; }
                        else { currentState = BONUS_LOSE; }
                        break;
                    }
                    if (isHit(x, y, thirteen))
                    {
                        //12
                        try2 = 12;
                        sum2 = 0;
                        for (int i = 0; i < 2; i++) {
                            k2[i] = rand() % 6 + 1;
                            sum2 += k2[i];
                        }
                        if (sum2 == try1 || sum2 == try2) { currentState = BONUS_WIN; }
                        else { currentState = BONUS_LOSE; }
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
                    if (isHit(x, y, Quit) || isHit(x, y, Rules) || isHit(x, y, Settings) || isHit(x, y, three) || isHit(x, y, four) || isHit(x, y, five) ||
                        isHit(x, y, six) || isHit(x, y, seven) || isHit(x, y, eight) || isHit(x, y, nine) || isHit(x, y, ten) || isHit(x, y, eleven) ||
                        isHit(x, y, twelve) || isHit(x, y, thirteen) || isHit(x, y, fourteen) || isHit(x, y, fifteen) || isHit(x, y, sixteen) ||
                        isHit(x, y, seventeen) || isHit(x, y, eightteen)) {
                        if (musEffects == 1) { sound(music); }
                    }
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
                        try1 = 3;
                        currentState = BONUS_GAME_3_2;
                        break;
                    }
                    if (isHit(x, y, four))
                    {
                        try1 = 4;
                        currentState = BONUS_GAME_3_2;
                        break;
                    }
                    if (isHit(x, y, five))
                    {
                        try1 = 5;
                        currentState = BONUS_GAME_3_2;
                        break;
                    }
                    if (isHit(x, y, six))
                    {
                        try1 = 6;
                        currentState = BONUS_GAME_3_2;
                        break;
                    }
                    if (isHit(x, y, seven))
                    {
                        try1 = 7;
                        currentState = BONUS_GAME_3_2;
                        break;
                    }
                    if (isHit(x, y, eight))
                    {
                        try1 = 8;
                        currentState = BONUS_GAME_3_2;
                        break;
                    }
                    if (isHit(x, y, nine))
                    {
                        try1 = 9;
                        currentState = BONUS_GAME_3_2;
                        break;
                    }
                    if (isHit(x, y, ten))
                    {
                        try1 = 10;
                        currentState = BONUS_GAME_3_2;
                        break;
                    }
                    if (isHit(x, y, eleven))
                    {
                        try1 = 11;
                        currentState = BONUS_GAME_3_2;
                        break;
                    }
                    if (isHit(x, y, twelve))
                    {
                        try1 = 12;
                        currentState = BONUS_GAME_3_2;
                        break;
                    }
                    if (isHit(x, y, thirteen))
                    {
                        try1 = 13;
                        currentState = BONUS_GAME_3_2;
                        break;
                    }
                    if (isHit(x, y, fourteen))
                    {
                        try1 = 14;
                        currentState = BONUS_GAME_3_2;
                        break;
                    }
                    if (isHit(x, y, fifteen))
                    {
                        try1 = 15;
                        currentState = BONUS_GAME_3_2;
                        break;
                    }
                    if (isHit(x, y, sixteen))
                    {
                        try1 = 16;
                        currentState = BONUS_GAME_3_2;
                        break;
                    }
                    if (isHit(x, y, seventeen))
                    {
                        try1 = 17;
                        currentState = BONUS_GAME_3_2;
                        break;
                    }
                    if (isHit(x, y, eightteen))
                    {
                        try1 = 18;
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
                    if (isHit(x, y, Quit) || isHit(x, y, Rules) || isHit(x, y, Settings) || isHit(x, y, three) || isHit(x, y, four) || isHit(x, y, five) ||
                        isHit(x, y, six) || isHit(x, y, seven) || isHit(x, y, eight) || isHit(x, y, nine) || isHit(x, y, ten) || isHit(x, y, eleven) ||
                        isHit(x, y, twelve) || isHit(x, y, thirteen) || isHit(x, y, fourteen) || isHit(x, y, fifteen) || isHit(x, y, sixteen) ||
                        isHit(x, y, seventeen) || isHit(x, y, eightteen)) {
                        if (musEffects == 1) { sound(music); }
                    }
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
                        try2 = 3;
                        sum2 = 0;
                        for (int i = 0; i < 3; i++) {
                            k3[i] = rand() % 5 + 1;
                            sum2 += k3[i];
                        }
                        if (sum2 == try1 || sum2 == try2) { currentState = BONUS_WIN; }
                        else { currentState = BONUS_LOSE; }
                        break;
                    }
                    if (isHit(x, y, four))
                    {
                        try2 = 4;
                        sum2 = 0;
                        for (int i = 0; i < 3; i++) {
                            k3[i] = rand() % 5 + 1;
                            sum2 += k3[i];
                        }
                        if (sum2 == try1 || sum2 == try2) { currentState = BONUS_WIN; }
                        else { currentState = BONUS_LOSE; }
                        break;
                    }
                    if (isHit(x, y, five))
                    {
                        try2 = 5;
                        sum2 = 0;
                        for (int i = 0; i < 3; i++) {
                            k3[i] = rand() % 5 + 1;
                            sum2 += k3[i];
                        }
                        if (sum2 == try1 || sum2 == try2) { currentState = BONUS_WIN; }
                        else { currentState = BONUS_LOSE; }
                        break;
                    }
                    if (isHit(x, y, six))
                    {
                        try2 = 6;
                        sum2 = 0;
                        for (int i = 0; i < 3; i++) {
                            k3[i] = rand() % 5 + 1;
                            sum2 += k3[i];
                        }
                        if (sum2 == try1 || sum2 == try2) { currentState = BONUS_WIN; }
                        else { currentState = BONUS_LOSE; }
                        break;
                    }
                    if (isHit(x, y, seven))
                    {
                        try2 = 7;
                        sum2 = 0;
                        for (int i = 0; i < 3; i++) {
                            k3[i] = rand() % 5 + 1;
                            sum2 += k3[i];
                        }
                        if (sum2 == try1 || sum2 == try2) { currentState = BONUS_WIN; }
                        else { currentState = BONUS_LOSE; }

                        break;
                    }
                    if (isHit(x, y, eight))
                    {
                        try2 = 8;
                        sum2 = 0;
                        for (int i = 0; i < 3; i++) {
                            k3[i] = rand() % 5 + 1;
                            sum2 += k3[i];
                        }
                        if (sum2 == try1 || sum2 == try2) { currentState = BONUS_WIN; }
                        else { currentState = BONUS_LOSE; }
                        break;
                    }
                    if (isHit(x, y, nine))
                    {
                        try2 = 9;
                        sum2 = 0;
                        for (int i = 0; i < 3; i++) {
                            k3[i] = rand() % 5 + 1;
                            sum2 += k3[i];
                        }
                        if (sum2 == try1 || sum2 == try2) { currentState = BONUS_WIN; }
                        else { currentState = BONUS_LOSE; }
                        break;
                    }
                    if (isHit(x, y, ten))
                    {
                        try2 = 10;
                        sum2 = 0;
                        for (int i = 0; i < 3; i++) {
                            k3[i] = rand() % 5 + 1;
                            sum2 += k3[i];
                        }
                        if (sum2 == try1 || sum2 == try2) { currentState = BONUS_WIN; }
                        else { currentState = BONUS_LOSE; }
                        break;
                    }
                    if (isHit(x, y, eleven))
                    {
                        try2 = 11;
                        sum2 = 0;
                        for (int i = 0; i < 3; i++) {
                            k3[i] = rand() % 5 + 1;
                            sum2 += k3[i];
                        }
                        if (sum2 == try1 || sum2 == try2) { currentState = BONUS_WIN; }
                        else { currentState = BONUS_LOSE; }
                        break;
                    }
                    if (isHit(x, y, twelve))
                    {
                        try2 = 12;
                        sum2 = 0;
                        for (int i = 0; i < 3; i++) {
                            k3[i] = rand() % 5 + 1;
                            sum2 += k3[i];
                        }
                        if (sum2 == try1 || sum2 == try2) { currentState = BONUS_WIN; }
                        else { currentState = BONUS_LOSE; }
                        break;
                    }
                    if (isHit(x, y, thirteen))
                    {
                        try2 = 13;
                        sum2 = 0;
                        for (int i = 0; i < 3; i++) {
                            k3[i] = rand() % 5 + 1;
                            sum2 += k3[i];
                        }
                        if (sum2 == try1 || sum2 == try2) { currentState = BONUS_WIN; }
                        else { currentState = BONUS_LOSE; }
                        break;
                    }
                    if (isHit(x, y, fourteen))
                    {
                        try2 = 14;
                        sum2 = 0;
                        for (int i = 0; i < 3; i++) {
                            k3[i] = rand() % 5 + 1;
                            sum2 += k3[i];
                        }
                        if (sum2 == try1 || sum2 == try2) { currentState = BONUS_WIN; }
                        else { currentState = BONUS_LOSE; }
                        break;
                    }
                    if (isHit(x, y, fifteen))
                    {
                        try2 = 15;
                        sum2 = 0;
                        for (int i = 0; i < 3; i++) {
                            k3[i] = rand() % 5 + 1;
                            sum2 += k3[i];
                        }
                        if (sum2 == try1 || sum2 == try2) { currentState = BONUS_WIN; }
                        else { currentState = BONUS_LOSE; }
                        break;
                    }
                    if (isHit(x, y, sixteen))
                    {
                        try2 = 16;
                        sum2 = 0;
                        for (int i = 0; i < 3; i++) {
                            k3[i] = rand() % 5 + 1;
                            sum2 += k3[i];
                        }
                        if (sum2 == try1 || sum2 == try2) { currentState = BONUS_WIN; }
                        else { currentState = BONUS_LOSE; }
                        break;
                    }
                    if (isHit(x, y, seventeen))
                    {
                        try2 = 17;
                        sum2 = 0;
                        for (int i = 0; i < 3; i++) {
                            k3[i] = rand() % 5 + 1;
                            sum2 += k3[i];
                        }
                        if (sum2 == try1 || sum2 == try2) { currentState = BONUS_WIN; }
                        else { currentState = BONUS_LOSE; }
                        break;
                    }
                    if (isHit(x, y, eightteen))
                    {
                        try2 = 18;
                        sum2 = 0;
                        for (int i = 0; i < 3; i++) {
                            k3[i] = rand() % 5 + 1;
                            sum2 += k3[i];
                        }
                        if (sum2 == try1 || sum2 == try2) { currentState = BONUS_WIN; }
                        else { currentState = BONUS_LOSE; }
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

            case BONUS_WIN:
            {
                draw(renderer, bonusWinTexture, bonusGame);
                if (choice_k == 1) {
                    _itoa_s(k1, text, 10);
                    textTexture = get_text_texture(renderer, text, my_font);
                    draw_text(renderer, textTexture, bonus_score);
                    if (k1 == 1) { draw(renderer, point1Texture, kub2); }
                    if (k1 == 2) { draw(renderer, point2Texture, kub2); }
                    if (k1 == 3) { draw(renderer, point3Texture, kub2); }
                    if (k1 == 4) { draw(renderer, point4Texture, kub2); }
                    if (k1 == 5) { draw(renderer, point5Texture, kub2); }
                    if (k1 == 6) { draw(renderer, point6Texture, kub2); }
                }
                if (choice_k == 2) {
                    int sum = 0;
                    for (int i = 0; i < 2; i++)
                    {
                        sum += k2[i];
                    }
                    _itoa_s(sum, text, 10);
                    textTexture = get_text_texture(renderer, text, my_font);
                    draw_text(renderer, textTexture, bonus_score);
                    //1 кубик
                    if (k2[0] == 1) { draw(renderer, point1Texture, kub1); }
                    if (k2[0] == 2) { draw(renderer, point2Texture, kub1); }
                    if (k2[0] == 3) { draw(renderer, point3Texture, kub1); }
                    if (k2[0] == 4) { draw(renderer, point4Texture, kub1); }
                    if (k2[0] == 5) { draw(renderer, point5Texture, kub1); }
                    if (k2[0] == 6) { draw(renderer, point6Texture, kub1); }
                    //2 кубик
                    if (k2[1] == 1) { draw(renderer, point1Texture, kub2); }
                    if (k2[1] == 2) { draw(renderer, point2Texture, kub2); }
                    if (k2[1] == 3) { draw(renderer, point3Texture, kub2); }
                    if (k2[1] == 4) { draw(renderer, point4Texture, kub2); }
                    if (k2[1] == 5) { draw(renderer, point5Texture, kub2); }
                    if (k2[1] == 6) { draw(renderer, point6Texture, kub2); }
                }
                if (choice_k == 3) {
                    int sum = 0;
                    for (int i = 0; i < 3; i++)
                    {
                        sum += k3[i];
                    }
                    _itoa_s(sum, text, 10);
                    textTexture = get_text_texture(renderer, text, my_font);
                    draw_text(renderer, textTexture, bonus_score);
                    if (k3[0] == 1) { draw(renderer, point1Texture, kub1); }
                    if (k3[0] == 2) { draw(renderer, point2Texture, kub1); }
                    if (k3[0] == 3) { draw(renderer, point3Texture, kub1); }
                    if (k3[0] == 4) { draw(renderer, point4Texture, kub1); }
                    if (k3[0] == 5) { draw(renderer, point5Texture, kub1); }
                    if (k3[0] == 6) { draw(renderer, point6Texture, kub1); }


                    if (k3[1] == 1) { draw(renderer, point1Texture, kub2); }
                    if (k3[1] == 2) { draw(renderer, point2Texture, kub2); }
                    if (k3[1] == 3) { draw(renderer, point3Texture, kub2); }
                    if (k3[1] == 4) { draw(renderer, point4Texture, kub2); }
                    if (k3[1] == 5) { draw(renderer, point5Texture, kub2); }
                    if (k3[1] == 6) { draw(renderer, point6Texture, kub2); }


                    if (k3[2] == 1) { draw(renderer, point1Texture, kub3); }
                    if (k3[2] == 2) { draw(renderer, point2Texture, kub3); }
                    if (k3[2] == 3) { draw(renderer, point3Texture, kub3); }
                    if (k3[2] == 4) { draw(renderer, point4Texture, kub3); }
                    if (k3[2] == 5) { draw(renderer, point5Texture, kub3); }
                    if (k3[2] == 6) { draw(renderer, point6Texture, kub3); }
                }
                if (players == 1) {
                    SDL_RenderPresent(renderer);
                    SDL_Delay(3000);
                    draw(renderer, welcomeMainGameTexture, bonusGame);
                    SDL_RenderPresent(renderer);
                    SDL_Delay(2000);
                    currentState = MAIN_GAME;
                    break;
                }
                if (players == 2)
                {
                    if (player == 2) {
                        SDL_RenderPresent(renderer);
                        SDL_Delay(3000);
                        draw(renderer, welcomeMainGameTexture, bonusGame);
                        SDL_RenderPresent(renderer);
                        SDL_Delay(2000);
                        currentState = MAIN_GAME;
                        break;
                    }
                    if (player == 1) {
                        SDL_RenderPresent(renderer);
                        SDL_Delay(3000);
                        player = 2;
                        currentState = CHOICE_PLAYER2;
                        break;
                    }
                    break;
                }

                break;
            }
            case BONUS_LOSE:
            {
                draw(renderer, bonusLoseTexture, bonusGame);
                if (choice_k == 1) {
                    _itoa_s(k1, text, 10);
                    textTexture = get_text_texture(renderer, text, my_font);
                    draw_text(renderer, textTexture, bonus_score);
                    if (k1 == 1) { draw(renderer, point1Texture, kub2); }
                    if (k1 == 2) { draw(renderer, point2Texture, kub2); }
                    if (k1 == 3) { draw(renderer, point3Texture, kub2); }
                    if (k1 == 4) { draw(renderer, point4Texture, kub2); }
                    if (k1 == 5) { draw(renderer, point5Texture, kub2); }
                    if (k1 == 6) { draw(renderer, point6Texture, kub2); }
                }
                if (choice_k == 2) {
                    int sum = 0;
                    for (int i = 0; i < 2; i++)
                    {
                        sum += k2[i];
                    }
                    _itoa_s(sum, text, 10);
                    textTexture = get_text_texture(renderer, text, my_font);
                    draw_text(renderer, textTexture, bonus_score);
                    //1 кубик
                    if (k2[0] == 1) { draw(renderer, point1Texture, kub1); }
                    if (k2[0] == 2) { draw(renderer, point2Texture, kub1); }
                    if (k2[0] == 3) { draw(renderer, point3Texture, kub1); }
                    if (k2[0] == 4) { draw(renderer, point4Texture, kub1); }
                    if (k2[0] == 5) { draw(renderer, point5Texture, kub1); }
                    if (k2[0] == 6) { draw(renderer, point6Texture, kub1); }

                    //2 кубик
                    if (k2[1] == 1) { draw(renderer, point1Texture, kub2); }
                    if (k2[1] == 2) { draw(renderer, point2Texture, kub2); }
                    if (k2[1] == 3) { draw(renderer, point3Texture, kub2); }
                    if (k2[1] == 4) { draw(renderer, point4Texture, kub2); }
                    if (k2[1] == 5) { draw(renderer, point5Texture, kub2); }
                    if (k2[1] == 6) { draw(renderer, point6Texture, kub2); }

                }
                if (choice_k == 3) {
                    int sum = 0;
                    for (int i = 0; i < 3; i++)
                    {
                        sum += k3[i];
                    }
                    _itoa_s(sum, text, 10);
                    textTexture = get_text_texture(renderer, text, my_font);
                    draw_text(renderer, textTexture, bonus_score);
                    if (k3[0] == 1) { draw(renderer, point1Texture, kub1); }
                    if (k3[0] == 2) { draw(renderer, point2Texture, kub1); }
                    if (k3[0] == 3) { draw(renderer, point3Texture, kub1); }
                    if (k3[0] == 4) { draw(renderer, point4Texture, kub1); }
                    if (k3[0] == 5) { draw(renderer, point5Texture, kub1); }
                    if (k3[0] == 6) { draw(renderer, point6Texture, kub1); }


                    if (k3[1] == 1) { draw(renderer, point1Texture, kub2); }
                    if (k3[1] == 2) { draw(renderer, point2Texture, kub2); }
                    if (k3[1] == 3) { draw(renderer, point3Texture, kub2); }
                    if (k3[1] == 4) { draw(renderer, point4Texture, kub2); }
                    if (k3[1] == 5) { draw(renderer, point5Texture, kub2); }
                    if (k3[1] == 6) { draw(renderer, point6Texture, kub2); }


                    if (k3[2] == 1) { draw(renderer, point1Texture, kub3); }
                    if (k3[2] == 2) { draw(renderer, point2Texture, kub3); }
                    if (k3[2] == 3) { draw(renderer, point3Texture, kub3); }
                    if (k3[2] == 4) { draw(renderer, point4Texture, kub3); }
                    if (k3[2] == 5) { draw(renderer, point5Texture, kub3); }
                    if (k3[2] == 6) { draw(renderer, point6Texture, kub3); }
                }
                if (players == 1) {
                    SDL_RenderPresent(renderer);
                    SDL_Delay(3000);
                    draw(renderer, welcomeMainGameTexture, bonusGame);
                    SDL_RenderPresent(renderer);
                    SDL_Delay(2000);
                    currentState = MAIN_GAME;
                    break;
                }
                if (players == 2)
                {
                    if (player == 2) {
                        SDL_RenderPresent(renderer);
                        SDL_Delay(3000);
                        draw(renderer, welcomeMainGameTexture, bonusGame);
                        SDL_RenderPresent(renderer);
                        SDL_Delay(2000);
                        currentState = MAIN_GAME;
                        break;
                    }
                    if (player == 1) {
                        SDL_RenderPresent(renderer);
                        SDL_Delay(3000);
                        player = 2;
                        currentState = CHOICE_PLAYER2;
                        break;
                    }
                    break;
                }

                break;
            }
            case MAIN_GAME:
                draw(renderer, mainGameTexture, bonusGame);
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
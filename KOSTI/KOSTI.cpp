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
    COMBINATIONS,
    RAFFLE1,
    RAFFLE2,
    BROSOK,
    PLAYER1,
    PLAYER2,
    HOD1,
    HOD2,
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

//бросаем 5 кубиков
int kub5(int k5[5]) {
    int sum = 0;
    int cnt1 = 0, cnt2 = 0, cnt3 = 0, cnt4 = 0, cnt5 = 0, cnt6 = 0;
    for (int i = 0; i < 5; i++) {
        if (k5[i] == 1) { ++cnt1; }
        else if (k5[i] == 2) { cnt2++; }
        else if (k5[i] == 3) { cnt3++; }
        else if (k5[i] == 4) { cnt4++; }
        else if (k5[i] == 5) { cnt5++; }
        else if (k5[i] == 6) { cnt6++; }
    }
    if (k5[0] == 1 && k5[1] == 2 && k5[2] == 3 && k5[3] == 4 && k5[4] == 5) { sum += 100; printf("\nSTRIT-1\n"); }
    else if (k5[0] == 2 && k5[1] == 3 && k5[2] == 4 && k5[3] == 5 && k5[4] == 6) { sum += 200; printf("\nSTRIT-2\n"); }
    else {
        if (cnt1 < 3) { sum += cnt1 * 10; }
        if (cnt5 < 3) { sum += cnt5 * 5; }
        //1
        if (cnt1 == 3) {
            sum += 10 * 10;
        }
        if (cnt1 == 4) {
            sum += 10 * 20;
        }
        if (cnt1 == 5) {
            sum += 10 * 100;
        }
        //2
        if (cnt2 == 3) {
            sum += 2 * 10;
        }
        if (cnt2 == 4) {
            sum += 2 * 20;
        }
        if (cnt2 == 5) {
            sum += 2 * 100;
        }
        //3
        if (cnt3 == 3) {
            sum += 3 * 10;
        }
        if (cnt3 == 4) {
            sum += 3 * 20;
        }
        if (cnt3 == 5) {
            sum += 3 * 100;
        }
        //4
        if (cnt4 == 3) {
            sum += 4 * 10;
        }
        if (cnt4 == 4) {
            sum += 4 * 20;
        }
        if (cnt4 == 5) {
            sum += 4 * 100;
        }
        //5
        if (cnt5 == 3) {
            sum += 5 * 10;
        }
        if (cnt5 == 4) {
            sum += 5 * 20;
        }
        if (cnt5 == 5) {
            sum += 5 * 100;
        }
        //6
        if (cnt6 == 3) {
            sum += 6 * 10;
        }
        if (cnt6 == 4) {
            sum += 6 * 20;
        }
        if (cnt6 == 5) {
            sum += 6 * 100;
        }
    }
    return sum;
}
//бросаем 4 кубика
int kub4(int k4[4]) {
    int sum = 0;
    int cnt1 = 0, cnt2 = 0, cnt3 = 0, cnt4 = 0, cnt5 = 0, cnt6 = 0;
    for (int i = 0; i < 4; i++) {
        if (k4[i] == 1) { ++cnt1; }
        else if (k4[i] == 2) { cnt2++; }
        else if (k4[i] == 3) { cnt3++; }
        else if (k4[i] == 4) { cnt4++; }
        else if (k4[i] == 5) { cnt5++; }
        else if (k4[i] == 6) { cnt6++; }
    }
    if (cnt1 < 3) { sum += cnt1 * 10; }
    if (cnt5 < 3) { sum += cnt5 * 5; }
    //1
    if (cnt1 == 3) {
        sum += 10 * 10;
    }
    if (cnt1 == 4) {
        sum += 10 * 20;
    }
    //2
    if (cnt2 == 3) {
        sum += 2 * 10;
    }
    if (cnt2 == 4) {
        sum += 2 * 20;
    }
    //3
    if (cnt3 == 3) {
        sum += 3 * 10;
    }
    if (cnt3 == 4) {
        sum += 3 * 20;
    }
    //4
    if (cnt4 == 3) {
        sum += 4 * 10;
    }
    if (cnt4 == 4) {
        sum += 4 * 20;
    }
    //5
    if (cnt5 == 3) {
        sum += 5 * 10;
    }
    if (cnt5 == 4) {
        sum += 5 * 20;
    }
    //6
    if (cnt6 == 3) {
        sum += 6 * 10;
    }
    if (cnt6 == 4) {
        sum += 6 * 20;
    }
    return sum;
}
//бросаем 3 кубика
int kub3(int k3[3]) {
    int sum = 0;
    int cnt1 = 0, cnt2 = 0, cnt3 = 0, cnt4 = 0, cnt5 = 0, cnt6 = 0;
    for (int i = 0; i < 3; i++) {
        if (k3[i] == 1) { ++cnt1; }
        else if (k3[i] == 2) { cnt2++; }
        else if (k3[i] == 3) { cnt3++; }
        else if (k3[i] == 4) { cnt4++; }
        else if (k3[i] == 5) { cnt5++; }
        else if (k3[i] == 6) { cnt6++; }
    }
    if (cnt1 < 3) { sum += cnt1 * 10; }
    if (cnt5 < 3) { sum += cnt5 * 5; }
    //1
    if (cnt1 == 3) {
        sum += 10 * 10;
    }
    //2
    if (cnt2 == 3) {
        sum += 2 * 10;
    }
    //3
    if (cnt3 == 3) {
        sum += 3 * 10;
    }
    //4
    if (cnt4 == 3) {
        sum += 4 * 10;
    }
    //5
    if (cnt5 == 3) {
        sum += 5 * 10;
    }
    //6
    if (cnt6 == 3) {
        sum += 6 * 10;
    }
    return sum;
}
//бросаем 2 кубика
int kub2(int k2[2]) {
    int sum = 0;
    int cnt1 = 0, cnt2 = 0, cnt3 = 0, cnt4 = 0, cnt5 = 0, cnt6 = 0;
    for (int i = 0; i < 2; i++) {
        if (k2[i] == 1) { ++cnt1; }
        else if (k2[i] == 2) { cnt2++; }
        else if (k2[i] == 3) { cnt3++; }
        else if (k2[i] == 4) { cnt4++; }
        else if (k2[i] == 5) { cnt5++; }
        else if (k2[i] == 6) { cnt6++; }
    }
    sum += cnt1 * 10;
    sum += cnt5 * 5;
    return sum;
}
//бросаем 1 кубик
int kub1(int k1) {
    int sum = 0;
    int cnt1 = 0, cnt2 = 0, cnt3 = 0, cnt4 = 0, cnt5 = 0, cnt6 = 0;
    if (k1 == 1) { cnt1++; }
    else if (k1 == 2) { cnt2++; }
    else if (k1 == 3) { cnt3++; }
    else if (k1 == 4) { cnt4++; }
    else if (k1 == 5) { cnt5++; }
    else if (k1 == 6) { cnt6++; }
    sum += cnt1 * 10;
    sum += cnt5 * 5;
    return sum;
}

//СЧИТАЕМ ИСПОЛЬЗОВАННЫЕ ИЗ 5 КУБИКИ
int cnt_kub5(int k5[5]) {
    int cnt = 0;
    int cnt1 = 0, cnt2 = 0, cnt3 = 0, cnt4 = 0, cnt5 = 0, cnt6 = 0;
    for (int i = 0; i < 5; i++) {
        if (k5[i] == 1) { cnt1++; }
        else if (k5[i] == 2) { cnt2++; }
        else if (k5[i] == 3) { cnt3++; }
        else if (k5[i] == 4) { cnt4++; }
        else if (k5[i] == 5) { cnt5++; }
        else if (k5[i] == 6) { cnt6++; }
    }
    if (k5[0] == 1 && k5[1] == 2 && k5[2] == 3 && k5[3] == 4 && k5[4] == 5) { cnt = 5; }
    else if (k5[0] == 2 && k5[1] == 3 && k5[2] == 4 && k5[3] == 5 && k5[4] == 6) { cnt = 5; }
    else {
        if (cnt1 < 3) { cnt += cnt1; }
        if (cnt5 < 3) { cnt += cnt5; }
        if (cnt1 == 3 || cnt2 == 3 || cnt3 == 3 || cnt4 == 3 || cnt5 == 3 || cnt6 == 3) {
            cnt += 3;
        }
        if (cnt1 == 4 || cnt2 == 4 || cnt3 == 4 || cnt4 == 4 || cnt5 == 4 || cnt6 == 4) {
            cnt += 4;
        }
        if (cnt1 == 5 || cnt2 == 5 || cnt3 == 5 || cnt4 == 5 || cnt5 == 5 || cnt6 == 5) {
            cnt += 5;
        }
    }
    return 5 - cnt;
}
//СЧИТАЕМ ИСПОЛЬЗОВАННЫЕ ИЗ 4 КУБИКИ
int cnt_kub4(int k4[4]) {
    int cnt = 0;
    int cnt1 = 0, cnt2 = 0, cnt3 = 0, cnt4 = 0, cnt5 = 0, cnt6 = 0;
    for (int i = 0; i < 4; i++) {
        if (k4[i] == 1) { cnt1++; }
        else if (k4[i] == 2) { cnt2++; }
        else if (k4[i] == 3) { cnt3++; }
        else if (k4[i] == 4) { cnt4++; }
        else if (k4[i] == 5) { cnt5++; }
        else if (k4[i] == 6) { cnt6++; }
    }
    if (cnt1 < 3) { cnt += cnt1; }
    if (cnt5 < 3) { cnt += cnt5; }
    if (cnt1 == 3 || cnt2 == 3 || cnt3 == 3 || cnt4 == 3 || cnt5 == 3 || cnt6 == 3) {
        cnt += 3;
    }
    if (cnt1 == 4 || cnt2 == 4 || cnt3 == 4 || cnt4 == 4 || cnt5 == 4 || cnt6 == 4) {
        cnt += 4;
    }
    return 4 - cnt;
}
//СЧИТАЕМ ИСПОЛЬЗОВАННЫЕ ИЗ 3 КУБИКИ
int cnt_kub3(int k3[3]) {
    int cnt = 0;
    int cnt1 = 0, cnt2 = 0, cnt3 = 0, cnt4 = 0, cnt5 = 0, cnt6 = 0;
    for (int i = 0; i < 3; i++) {
        if (k3[i] == 1) { cnt1++; }
        else if (k3[i] == 2) { cnt2++; }
        else if (k3[i] == 3) { cnt3++; }
        else if (k3[i] == 4) { cnt4++; }
        else if (k3[i] == 5) { cnt5++; }
        else if (k3[i] == 6) { cnt6++; }
    }
    if (cnt1 < 3) { cnt += cnt1; }
    if (cnt5 < 3) { cnt += cnt5; }
    if (cnt1 == 3 || cnt2 == 3 || cnt3 == 3 || cnt4 == 3 || cnt5 == 3 || cnt6 == 3) {
        cnt += 3;
    }
    return 3 - cnt;
}
//СЧИТАЕМ ИСПОЛЬЗОВАННЫЕ ИЗ 2 КУБИКИ
int cnt_kub2(int k2[2]) {
    int cnt = 0;
    int cnt1 = 0, cnt2 = 0, cnt3 = 0, cnt4 = 0, cnt5 = 0, cnt6 = 0;
    for (int i = 0; i < 2; i++) {
        if (k2[i] == 1) { cnt1++; }
        else if (k2[i] == 2) { cnt2++; }
        else if (k2[i] == 3) { cnt3++; }
        else if (k2[i] == 4) { cnt4++; }
        else if (k2[i] == 5) { cnt5++; }
        else if (k2[i] == 6) { cnt6++; }
    }
    cnt += cnt1;
    cnt += cnt5;
    return 2 - cnt;
}
//СЧИТАЕМ ИСПОЛЬЗОВАННЫЕ ИЗ 1 КУБИКИ
int cnt_kub1(int k1) {
    int cnt = 0;
    int cnt1 = 0, cnt2 = 0, cnt3 = 0, cnt4 = 0, cnt5 = 0, cnt6 = 0;

    if (k1 == 1) { cnt1++; }
    else if (k1 == 2) { cnt2++; }
    else if (k1 == 3) { cnt3++; }
    else if (k1 == 4) { cnt4++; }
    else if (k1 == 5) { cnt5++; }
    else if (k1 == 6) { cnt6++; }

    cnt += cnt1;
    cnt += cnt5;
    return 1 - cnt;
}

enum step {
    player1,
    player2,
};
enum brosok1 {
    kubik1,
    kubik2,
    kubik3,
    kubik4,
    kubik5,
};
int main(int argc, char** argv) {
    srand(time(NULL));
    setlocale(LC_ALL, "Rus");
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

    SDL_Surface* mainGameImage = IMG_Load("mainGame.bmp"); //главная игры 
    SDL_SetColorKey(mainGameImage, SDL_TRUE, SDL_MapRGB(mainGameImage->format, 255, 255, 255));
    SDL_Texture* mainGameTexture = SDL_CreateTextureFromSurface(renderer, mainGameImage);
    SDL_FreeSurface(mainGameImage);

    SDL_Surface* mainStopImage = IMG_Load("mainStop.bmp"); //кубики остановились 
    SDL_SetColorKey(mainStopImage, SDL_TRUE, SDL_MapRGB(mainStopImage->format, 255, 255, 255));
    SDL_Texture* mainStopTexture = SDL_CreateTextureFromSurface(renderer, mainStopImage);
    SDL_FreeSurface(mainStopImage);

    SDL_Surface* mainRecordImage = IMG_Load("mainRecord.bmp"); //результат записался
    SDL_SetColorKey(mainRecordImage, SDL_TRUE, SDL_MapRGB(mainRecordImage->format, 255, 255, 255));
    SDL_Texture* mainRecordTexture = SDL_CreateTextureFromSurface(renderer, mainRecordImage);
    SDL_FreeSurface(mainRecordImage);

    SDL_Surface* combinationImage = IMG_Load("combination.bmp"); //кнопка комбинаций
    SDL_SetColorKey(combinationImage, SDL_TRUE, SDL_MapRGB(combinationImage->format, 255, 255, 255));
    SDL_Texture* combinationTexture = SDL_CreateTextureFromSurface(renderer, combinationImage);
    SDL_FreeSurface(combinationImage);

    SDL_Surface* combinationsImage = IMG_Load("combinations.bmp"); //окно комбинаций
    SDL_SetColorKey(combinationsImage, SDL_TRUE, SDL_MapRGB(combinationsImage->format, 255, 255, 255));
    SDL_Texture* combinationsTexture = SDL_CreateTextureFromSurface(renderer, combinationsImage);
    SDL_FreeSurface(combinationsImage);

    SDL_Surface* throwImage = IMG_Load("throw.bmp"); //окно комбинаций
    SDL_SetColorKey(throwImage, SDL_TRUE, SDL_MapRGB(throwImage->format, 255, 255, 255));
    SDL_Texture* throwTexture = SDL_CreateTextureFromSurface(renderer, throwImage);
    SDL_FreeSurface(throwImage);

    SDL_Surface* stopImage = IMG_Load("stop.bmp"); //окно комбинаций
    SDL_SetColorKey(stopImage, SDL_TRUE, SDL_MapRGB(stopImage->format, 255, 255, 255));
    SDL_Texture* stopTexture = SDL_CreateTextureFromSurface(renderer, stopImage);
    SDL_FreeSurface(stopImage);

    SDL_Surface* recordImage = IMG_Load("record.bmp"); //окно комбинаций
    SDL_SetColorKey(recordImage, SDL_TRUE, SDL_MapRGB(recordImage->format, 255, 255, 255));
    SDL_Texture* recordTexture = SDL_CreateTextureFromSurface(renderer, recordImage);
    SDL_FreeSurface(recordImage);

    SDL_Surface* firstPlayerImage = IMG_Load("firstPlayer.bmp"); // игрок 1 
    SDL_SetColorKey(firstPlayerImage, SDL_TRUE, SDL_MapRGB(firstPlayerImage->format, 255, 255, 255));
    SDL_Texture* firstPlayerTexture = SDL_CreateTextureFromSurface(renderer, firstPlayerImage);
    SDL_FreeSurface(firstPlayerImage);

    SDL_Surface* secondPlayerImage = IMG_Load("secondPlayer.bmp"); // игрок 2
    SDL_SetColorKey(secondPlayerImage, SDL_TRUE, SDL_MapRGB(secondPlayerImage->format, 255, 255, 255));
    SDL_Texture* secondPlayerTexture = SDL_CreateTextureFromSurface(renderer, secondPlayerImage);
    SDL_FreeSurface(secondPlayerImage);

    SDL_Surface* raffle1Image = IMG_Load("raffle1.bmp"); // розыгрыш 1
    SDL_SetColorKey(raffle1Image, SDL_TRUE, SDL_MapRGB(raffle1Image->format, 255, 255, 255));
    SDL_Texture* raffle1Texture = SDL_CreateTextureFromSurface(renderer, raffle1Image);
    SDL_FreeSurface(raffle1Image);

    SDL_Surface* raffle2Image = IMG_Load("raffle2.bmp"); // розыгрыш 2
    SDL_SetColorKey(raffle2Image, SDL_TRUE, SDL_MapRGB(raffle2Image->format, 255, 255, 255));
    SDL_Texture* raffle2Texture = SDL_CreateTextureFromSurface(renderer, raffle2Image);
    SDL_FreeSurface(raffle2Image);

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
    SDL_Rect kube1 = { 590,268,100,100 };
    SDL_Rect kube2 = { 714, 268, 100, 100 };
    SDL_Rect kube3 = { 838,268,100,100 };

    SDL_Rect onFonMusic = { 28,411,717,100 };
    SDL_Rect offFonMusic = { 28,536,717,100 };

    SDL_Rect onMusEffects = { 790,406,717,100 };
    SDL_Rect offMusEffects = { 790,531,717,100 };

    SDL_Rect scorePlayer1 = { 107, 259, 206, 73 };
    SDL_Rect scorePlayer2 = { 1224, 259, 206, 73 };
    SDL_Rect droppedScore = { 671, 505, 206, 73 };
    SDL_Rect combinationsReference = { 894, 0 , 80, 80 };

    SDL_Rect brosok = { 624, 432, 300, 73 };
    SDL_Rect stop = { 624, 432, 300, 73 };

    SDL_Rect cube1 = { 471, 282, 100, 100 };
    SDL_Rect cube2 = { 595, 282, 100, 100 };
    SDL_Rect cube3 = { 719, 282, 100, 100 };
    SDL_Rect cube4 = { 843, 282, 100, 100 };
    SDL_Rect cube5 = { 967, 282, 100, 100 };

    SDL_Rect player1 = { 60, 106, 300, 50 };
    SDL_Rect player2 = { 1178, 106, 300, 50 };


    SDL_Event event;
    State currentState = MENU;
    State currentPrev = MENU;
    brosok1 cur_brosok = kubik5;

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
    int score1 = 0, score2 = 0;

    int raffle1 = 0, raffle2 = 0;
    int firstPlayer = 1;

    int tmpSum = 0;

    int begin_game = 0;

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
                        if (currentPrev == MAIN_GAME) {
                            currentState = MAIN_GAME;
                        }
                        else { currentState = MENU; }
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
                        if (currentPrev == MAIN_GAME) {
                            currentState = MAIN_GAME;
                        }
                        else { currentState = MENU; } break;
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
                        if (currentPrev == MAIN_GAME) {
                            currentState = MAIN_GAME;
                        }
                        else { currentState = MENU; } break;
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
                                currentState = RAFFLE1;
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

            case BONUS_WIN:
            {
                draw(renderer, bonusWinTexture, bonusGame);
                if (choice_k == 1) {
                    _itoa_s(k1, text, 10);
                    textTexture = get_text_texture(renderer, text, my_font);
                    draw_text(renderer, textTexture, bonus_score);
                    if (k1 == 1) { draw(renderer, point1Texture, kube2); }
                    if (k1 == 2) { draw(renderer, point2Texture, kube2); }
                    if (k1 == 3) { draw(renderer, point3Texture, kube2); }
                    if (k1 == 4) { draw(renderer, point4Texture, kube2); }
                    if (k1 == 5) { draw(renderer, point5Texture, kube2); }
                    if (k1 == 6) { draw(renderer, point6Texture, kube2); }
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
                    if (k2[0] == 1) { draw(renderer, point1Texture, kube1); }
                    if (k2[0] == 2) { draw(renderer, point2Texture, kube1); }
                    if (k2[0] == 3) { draw(renderer, point3Texture, kube1); }
                    if (k2[0] == 4) { draw(renderer, point4Texture, kube1); }
                    if (k2[0] == 5) { draw(renderer, point5Texture, kube1); }
                    if (k2[0] == 6) { draw(renderer, point6Texture, kube1); }
                    //2 кубик
                    if (k2[1] == 1) { draw(renderer, point1Texture, kube2); }
                    if (k2[1] == 2) { draw(renderer, point2Texture, kube2); }
                    if (k2[1] == 3) { draw(renderer, point3Texture, kube2); }
                    if (k2[1] == 4) { draw(renderer, point4Texture, kube2); }
                    if (k2[1] == 5) { draw(renderer, point5Texture, kube2); }
                    if (k2[1] == 6) { draw(renderer, point6Texture, kube2); }
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
                    if (k3[0] == 1) { draw(renderer, point1Texture, kube1); }
                    if (k3[0] == 2) { draw(renderer, point2Texture, kube1); }
                    if (k3[0] == 3) { draw(renderer, point3Texture, kube1); }
                    if (k3[0] == 4) { draw(renderer, point4Texture, kube1); }
                    if (k3[0] == 5) { draw(renderer, point5Texture, kube1); }
                    if (k3[0] == 6) { draw(renderer, point6Texture, kube1); }


                    if (k3[1] == 1) { draw(renderer, point1Texture, kube2); }
                    if (k3[1] == 2) { draw(renderer, point2Texture, kube2); }
                    if (k3[1] == 3) { draw(renderer, point3Texture, kube2); }
                    if (k3[1] == 4) { draw(renderer, point4Texture, kube2); }
                    if (k3[1] == 5) { draw(renderer, point5Texture, kube2); }
                    if (k3[1] == 6) { draw(renderer, point6Texture, kube2); }


                    if (k3[2] == 1) { draw(renderer, point1Texture, kube3); }
                    if (k3[2] == 2) { draw(renderer, point2Texture, kube3); }
                    if (k3[2] == 3) { draw(renderer, point3Texture, kube3); }
                    if (k3[2] == 4) { draw(renderer, point4Texture, kube3); }
                    if (k3[2] == 5) { draw(renderer, point5Texture, kube3); }
                    if (k3[2] == 6) { draw(renderer, point6Texture, kube3); }
                }
                if (players == 1) {
                    score1 = 50;
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
                        score2 = 50;
                        SDL_RenderPresent(renderer);
                        SDL_Delay(3000);
                        draw(renderer, welcomeMainGameTexture, bonusGame);
                        SDL_RenderPresent(renderer);
                        SDL_Delay(2000);
                        currentState = RAFFLE1;
                        break;
                    }
                    if (player == 1) {
                        SDL_RenderPresent(renderer);
                        SDL_Delay(3000);
                        score1 = 50;
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
                    if (k1 == 1) { draw(renderer, point1Texture, kube2); }
                    if (k1 == 2) { draw(renderer, point2Texture, kube2); }
                    if (k1 == 3) { draw(renderer, point3Texture, kube2); }
                    if (k1 == 4) { draw(renderer, point4Texture, kube2); }
                    if (k1 == 5) { draw(renderer, point5Texture, kube2); }
                    if (k1 == 6) { draw(renderer, point6Texture, kube2); }
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
                    if (k2[0] == 1) { draw(renderer, point1Texture, kube1); }
                    if (k2[0] == 2) { draw(renderer, point2Texture, kube1); }
                    if (k2[0] == 3) { draw(renderer, point3Texture, kube1); }
                    if (k2[0] == 4) { draw(renderer, point4Texture, kube1); }
                    if (k2[0] == 5) { draw(renderer, point5Texture, kube1); }
                    if (k2[0] == 6) { draw(renderer, point6Texture, kube1); }

                    //2 кубик
                    if (k2[1] == 1) { draw(renderer, point1Texture, kube2); }
                    if (k2[1] == 2) { draw(renderer, point2Texture, kube2); }
                    if (k2[1] == 3) { draw(renderer, point3Texture, kube2); }
                    if (k2[1] == 4) { draw(renderer, point4Texture, kube2); }
                    if (k2[1] == 5) { draw(renderer, point5Texture, kube2); }
                    if (k2[1] == 6) { draw(renderer, point6Texture, kube2); }

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
                    if (k3[0] == 1) { draw(renderer, point1Texture, kube1); }
                    if (k3[0] == 2) { draw(renderer, point2Texture, kube1); }
                    if (k3[0] == 3) { draw(renderer, point3Texture, kube1); }
                    if (k3[0] == 4) { draw(renderer, point4Texture, kube1); }
                    if (k3[0] == 5) { draw(renderer, point5Texture, kube1); }
                    if (k3[0] == 6) { draw(renderer, point6Texture, kube1); }


                    if (k3[1] == 1) { draw(renderer, point1Texture, kube2); }
                    if (k3[1] == 2) { draw(renderer, point2Texture, kube2); }
                    if (k3[1] == 3) { draw(renderer, point3Texture, kube2); }
                    if (k3[1] == 4) { draw(renderer, point4Texture, kube2); }
                    if (k3[1] == 5) { draw(renderer, point5Texture, kube2); }
                    if (k3[1] == 6) { draw(renderer, point6Texture, kube2); }


                    if (k3[2] == 1) { draw(renderer, point1Texture, kube3); }
                    if (k3[2] == 2) { draw(renderer, point2Texture, kube3); }
                    if (k3[2] == 3) { draw(renderer, point3Texture, kube3); }
                    if (k3[2] == 4) { draw(renderer, point4Texture, kube3); }
                    if (k3[2] == 5) { draw(renderer, point5Texture, kube3); }
                    if (k3[2] == 6) { draw(renderer, point6Texture, kube3); }
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
                        currentState = RAFFLE1;
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


            case RAFFLE1:
                draw(renderer, raffle1Texture, bonusGame);
                draw(renderer, firstPlayerTexture, player1);
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
                        currentPrev = MAIN_GAME;
                        currentState = SETTINGS;
                        break;
                    }
                    if (isHit(x, y, combinationsReference)) {
                        currentState = COMBINATIONS;
                        break;
                    }
                    if (isHit(x, y, brosok)) {
                        raffle1 = rand() % 6 + 1;
                        if (raffle1 == 1) { draw(renderer, point1Texture, cube3); }
                        if (raffle1 == 2) { draw(renderer, point2Texture, cube3); }
                        if (raffle1 == 3) { draw(renderer, point3Texture, cube3); }
                        if (raffle1 == 4) { draw(renderer, point4Texture, cube3); }
                        if (raffle1 == 5) { draw(renderer, point5Texture, cube3); }
                        if (raffle1 == 6) { draw(renderer, point6Texture, cube3); }
                        SDL_RenderPresent(renderer);
                        SDL_Delay(2000);
                        currentState = RAFFLE2;
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
                    if (isHit(x, y, combinationsReference)) {
                        draw(renderer, combinationTexture, combinationsReference);
                        break;
                    }
                    if (isHit(x, y, brosok)) {
                        draw(renderer, throwTexture, brosok);
                        break;
                    }
                }
                break;
            case RAFFLE2:
                draw(renderer, raffle2Texture, bonusGame);
                draw(renderer, secondPlayerTexture, player2);
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
                        currentPrev = MAIN_GAME;
                        currentState = SETTINGS;
                        break;
                    }
                    if (isHit(x, y, combinationsReference)) {
                        currentState = COMBINATIONS;
                        break;
                    }
                    if (isHit(x, y, brosok)) {
                        raffle2 = rand() % 6 + 1;
                        if (raffle2 == 1) { draw(renderer, point1Texture, cube3); }
                        if (raffle2 == 2) { draw(renderer, point2Texture, cube3); }
                        if (raffle2 == 3) { draw(renderer, point3Texture, cube3); }
                        if (raffle2 == 4) { draw(renderer, point4Texture, cube3); }
                        if (raffle2 == 5) { draw(renderer, point5Texture, cube3); }
                        if (raffle2 == 6) { draw(renderer, point6Texture, cube3); }
                        SDL_RenderPresent(renderer);
                        SDL_Delay(2000);
                        if (raffle1 == raffle2) { currentState = RAFFLE1; break; }
                        else { currentState = MAIN_GAME; }
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
                    if (isHit(x, y, combinationsReference)) {
                        draw(renderer, combinationTexture, combinationsReference);
                        break;
                    }
                    if (isHit(x, y, brosok)) {
                        draw(renderer, throwTexture, brosok);
                        break;
                    }
                }
                break;


            case MAIN_GAME:
                draw(renderer, mainGameTexture, bonusGame);
                if (players == 2) {
                    if (raffle1 > raffle2) { firstPlayer = 1; }
                    if (raffle2 > raffle1) { firstPlayer = 2; }
                    if (firstPlayer == 1) { /*draw(renderer, firstPlayerTexture, player1);*/ currentState = PLAYER1; break; }
                    if (firstPlayer == 2) { /*draw(renderer, secondPlayerTexture, player2);*/ currentState = PLAYER2; break; }
                }
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
                        currentPrev = MAIN_GAME;
                        currentState = SETTINGS;
                        break;
                    }
                    if (isHit(x, y, combinationsReference)) {
                        currentState = COMBINATIONS;
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
                    if (isHit(x, y, combinationsReference)) {
                        draw(renderer, combinationTexture, combinationsReference);
                        break;
                    }
                    if (isHit(x, y, brosok)) {
                        draw(renderer, throwTexture, brosok);
                        break;
                    }
                }
                break;

            case PLAYER1:
                draw(renderer, mainGameTexture, bonusGame);
                draw(renderer, firstPlayerTexture, player1);
                if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT)
                {
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
                        currentPrev = MAIN_GAME;
                        currentState = SETTINGS;
                        break;
                    }
                    if (isHit(x, y, combinationsReference)) {
                        currentState = COMBINATIONS;
                        break;
                    }
                    if (isHit(x, y, brosok)) {
                        if (score1 < 50)
                        {
                            cur_brosok = kubik5;
                            currentState = HOD1;
                        }
                        if (score1 > 50) {

                            currentState = PLAYER1;
                        }
                        break;
                    }

                }
                if (event.type == SDL_MOUSEMOTION) {
                    SDL_GetMouseState(&x, &y);
                    if (isHit(x, y, brosok)) {
                        draw(renderer, throwTexture, brosok);
                        break;
                    }
                }
                break;


            case PLAYER2:
                draw(renderer, mainGameTexture, bonusGame);
                draw(renderer, secondPlayerTexture, player2);
                if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT)
                {
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
                        currentPrev = MAIN_GAME;
                        currentState = SETTINGS;
                        break;
                    }
                    if (isHit(x, y, combinationsReference)) {
                        currentState = COMBINATIONS;
                        break;
                    }
                    if (isHit(x, y, brosok)) {
                        if (score2 < 50)
                        {
                            cur_brosok = kubik5;
                            currentState = HOD1;

                        }
                        if (score2 > 50) {
                            currentState = PLAYER2;
                        }
                        break;
                    }
                }
                if (event.type == SDL_MOUSEMOTION) {
                    SDL_GetMouseState(&x, &y);
                    if (isHit(x, y, brosok)) {
                        draw(renderer, throwTexture, brosok);
                        break;
                    }
                }
                break;


            case HOD1:
            {
                if (firstPlayer == 1) { draw(renderer, firstPlayerTexture, player1); }
                if (firstPlayer == 2) { draw(renderer, secondPlayerTexture, player2); }
                int sum = 0;
                int k1, k2[2], k3[3], k4[4], k5[5];
                int cnt1 = 0, cnt2 = 0, cnt3 = 0, cnt4 = 0, cnt5 = 0, cnt6 = 0;
                if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT) {
                    switch (cur_brosok) {
                    case kubik5:
                        SDL_GetMouseState(&x, &y);
                        if (isHit(x, y, brosok)) {
                            draw(renderer, mainGameTexture, bonusGame);
                            cnt1 = 0, cnt2 = 0, cnt3 = 0, cnt4 = 0, cnt5 = 0, cnt6 = 0;
                            for (int i = 0; i < 5; i++) {
                                k5[i] = rand() % 6 + 1;
                                //printf("%d  ", k5[i]);
                            }

                            for (int i = 0; i < 5; i++) {
                                if (i == 0) {
                                    if (k5[i] == 1) { draw(renderer, point1Texture, cube1); }
                                    if (k5[i] == 2) { draw(renderer, point2Texture, cube1); }
                                    if (k5[i] == 3) { draw(renderer, point3Texture, cube1); }
                                    if (k5[i] == 4) { draw(renderer, point4Texture, cube1); }
                                    if (k5[i] == 5) { draw(renderer, point5Texture, cube1); }
                                    if (k5[i] == 6) { draw(renderer, point6Texture, cube1); }
                                }
                                if (i == 1) {
                                    if (k5[i] == 1) { draw(renderer, point1Texture, cube2); }
                                    if (k5[i] == 2) { draw(renderer, point2Texture, cube2); }
                                    if (k5[i] == 3) { draw(renderer, point3Texture, cube2); }
                                    if (k5[i] == 4) { draw(renderer, point4Texture, cube2); }
                                    if (k5[i] == 5) { draw(renderer, point5Texture, cube2); }
                                    if (k5[i] == 6) { draw(renderer, point6Texture, cube2); }
                                }
                                if (i == 2) {
                                    if (k5[i] == 1) { draw(renderer, point1Texture, cube3); }
                                    if (k5[i] == 2) { draw(renderer, point2Texture, cube3); }
                                    if (k5[i] == 3) { draw(renderer, point3Texture, cube3); }
                                    if (k5[i] == 4) { draw(renderer, point4Texture, cube3); }
                                    if (k5[i] == 5) { draw(renderer, point5Texture, cube3); }
                                    if (k5[i] == 6) { draw(renderer, point6Texture, cube3); }
                                }
                                if (i == 3) {
                                    if (k5[i] == 1) { draw(renderer, point1Texture, cube4); }
                                    if (k5[i] == 2) { draw(renderer, point2Texture, cube4); }
                                    if (k5[i] == 3) { draw(renderer, point3Texture, cube4); }
                                    if (k5[i] == 4) { draw(renderer, point4Texture, cube4); }
                                    if (k5[i] == 5) { draw(renderer, point5Texture, cube4); }
                                    if (k5[i] == 6) { draw(renderer, point6Texture, cube4); }
                                }
                                if (i == 4) {
                                    if (k5[i] == 1) { draw(renderer, point1Texture, cube5); }
                                    if (k5[i] == 2) { draw(renderer, point2Texture, cube5); }
                                    if (k5[i] == 3) { draw(renderer, point3Texture, cube5); }
                                    if (k5[i] == 4) { draw(renderer, point4Texture, cube5); }
                                    if (k5[i] == 5) { draw(renderer, point5Texture, cube5); }
                                    if (k5[i] == 6) { draw(renderer, point6Texture, cube5); }
                                }
                            }

                            if (cnt_kub5(k5) == 0) {
                                sum += kub5(k5);
                                if (sum < 50) { cur_brosok = kubik5; }
                                else {
                                    if (firstPlayer == 1) { score1 += sum; }
                                    if (firstPlayer == 2) { score2 += sum; }
                                }
                            }
                            if (cnt_kub5(k5) == 1) {
                                sum += kub5(k5);
                                if (sum < 50) { cur_brosok = kubik1; }
                                else {
                                    if (firstPlayer == 1) { score1 += sum; }
                                    if (firstPlayer == 2) { score2 += sum; }
                                }
                            }
                            if (cnt_kub5(k5) == 2) {
                                sum += kub5(k5);
                                if (sum < 50) { cur_brosok = kubik2; }
                                else {
                                    if (firstPlayer == 1) { score1 += sum; }
                                    if (firstPlayer == 2) { score2 += sum; }
                                }
                            }
                            if (cnt_kub5(k5) == 3) {
                                sum += kub5(k5);
                                if (sum < 50) { cur_brosok = kubik3; }
                                else {
                                    if (firstPlayer == 1) { score1 += sum; }
                                    if (firstPlayer == 2) { score2 += sum; }
                                }
                            }
                            if (cnt_kub5(k5) == 4) {
                                sum += kub5(k5);
                                if (sum < 50) { cur_brosok = kubik4; }
                                else {
                                    if (firstPlayer == 1) { score1 += sum; }
                                    if (firstPlayer == 2) { score2 += sum; }
                                }
                            }
                            if (cnt_kub5(k5) == 5) {
                                sum = 0;
                                SDL_RenderPresent(renderer);
                                SDL_Delay(1500);
                                if (firstPlayer == 1) { firstPlayer = 2;  currentState = PLAYER2; break; }
                                if (firstPlayer == 2) { firstPlayer = 1;  currentState = PLAYER1; break; }
                            }

                            SDL_RenderPresent(renderer);
                            //SDL_Delay(2000);
                        }
                        //SDL_RenderPresent(renderer);
                        break;
                    case kubik4:
                        SDL_GetMouseState(&x, &y);
                        if (isHit(x, y, brosok)) {
                            //SDL_RenderPresent(renderer);
                            draw(renderer, mainGameTexture, bonusGame);
                            cnt1 = 0, cnt2 = 0, cnt3 = 0, cnt4 = 0, cnt5 = 0, cnt6 = 0;
                            for (int i = 0; i < 4; i++) {
                                k4[i] = rand() % 6 + 1;
                                //printf("%d  ", k4[i]);
                            }

                            for (int i = 0; i < 4; i++) {
                                if (i == 0) {
                                    if (k4[i] == 1) { draw(renderer, point1Texture, cube1); }
                                    if (k4[i] == 2) { draw(renderer, point2Texture, cube1); }
                                    if (k4[i] == 3) { draw(renderer, point3Texture, cube1); }
                                    if (k4[i] == 4) { draw(renderer, point4Texture, cube1); }
                                    if (k4[i] == 5) { draw(renderer, point5Texture, cube1); }
                                    if (k4[i] == 6) { draw(renderer, point6Texture, cube1); }
                                }
                                if (i == 1) {
                                    if (k4[i] == 1) { draw(renderer, point1Texture, cube2); }
                                    if (k4[i] == 2) { draw(renderer, point2Texture, cube2); }
                                    if (k4[i] == 3) { draw(renderer, point3Texture, cube2); }
                                    if (k4[i] == 4) { draw(renderer, point4Texture, cube2); }
                                    if (k4[i] == 5) { draw(renderer, point5Texture, cube2); }
                                    if (k4[i] == 6) { draw(renderer, point6Texture, cube2); }
                                }
                                if (i == 2) {
                                    if (k4[i] == 1) { draw(renderer, point1Texture, cube3); }
                                    if (k4[i] == 2) { draw(renderer, point2Texture, cube3); }
                                    if (k4[i] == 3) { draw(renderer, point3Texture, cube3); }
                                    if (k4[i] == 4) { draw(renderer, point4Texture, cube3); }
                                    if (k4[i] == 5) { draw(renderer, point5Texture, cube3); }
                                    if (k4[i] == 6) { draw(renderer, point6Texture, cube3); }
                                }
                                if (i == 3) {
                                    if (k4[i] == 1) { draw(renderer, point1Texture, cube4); }
                                    if (k4[i] == 2) { draw(renderer, point2Texture, cube4); }
                                    if (k4[i] == 3) { draw(renderer, point3Texture, cube4); }
                                    if (k4[i] == 4) { draw(renderer, point4Texture, cube4); }
                                    if (k4[i] == 5) { draw(renderer, point5Texture, cube4); }
                                    if (k4[i] == 6) { draw(renderer, point6Texture, cube4); }
                                }
                            }

                            if (cnt_kub4(k4) == 0) {
                                sum += kub4(k4);
                                if (sum < 50) { cur_brosok = kubik5; }
                                else {
                                    if (firstPlayer == 1) { score1 += sum; }
                                    if (firstPlayer == 2) { score2 += sum; }
                                }
                            }
                            if (cnt_kub4(k4) == 1) {
                                sum += kub4(k4);
                                if (sum < 50) { cur_brosok = kubik1; }
                                else {
                                    if (firstPlayer == 1) { score1 += sum; }
                                    if (firstPlayer == 2) { score2 += sum; }
                                }
                            }
                            if (cnt_kub4(k4) == 2) {
                                sum += kub4(k4);
                                if (sum < 50) { cur_brosok = kubik2; }
                                else {
                                    if (firstPlayer == 1) { score1 += sum; }
                                    if (firstPlayer == 2) { score2 += sum; }
                                }
                            }
                            if (cnt_kub4(k4) == 3) {
                                sum += kub4(k4);
                                if (sum < 50) { cur_brosok = kubik3; }
                                else {
                                    if (firstPlayer == 1) { score1 += sum; }
                                    if (firstPlayer == 2) { score2 += sum; }
                                }
                            }
                            if (cnt_kub4(k4) == 4) {
                                sum = 0;
                                SDL_RenderPresent(renderer);
                                SDL_Delay(1500);
                                if (firstPlayer == 1) { firstPlayer = 2;  currentState = PLAYER2; break; }
                                if (firstPlayer == 2) { firstPlayer = 1;  currentState = PLAYER1; break; }
                            }
                            SDL_RenderPresent(renderer);
                            //SDL_Delay(2000);
                            //SDL_RenderPresent(renderer);
                        }
                        break;
                    case kubik3:
                        SDL_GetMouseState(&x, &y);
                        if (isHit(x, y, brosok)) {
                            //SDL_RenderPresent(renderer);
                            draw(renderer, mainGameTexture, bonusGame);
                            cnt1 = 0, cnt2 = 0, cnt3 = 0, cnt4 = 0, cnt5 = 0, cnt6 = 0;
                            for (int i = 0; i < 3; i++) {
                                k3[i] = rand() % 6 + 1;
                                //printf("%d  ", k3[i]);
                            }

                            for (int i = 0; i < 3; i++) {
                                if (i == 0) {
                                    if (k3[i] == 1) { draw(renderer, point1Texture, cube2); }
                                    if (k3[i] == 2) { draw(renderer, point2Texture, cube2); }
                                    if (k3[i] == 3) { draw(renderer, point3Texture, cube2); }
                                    if (k3[i] == 4) { draw(renderer, point4Texture, cube2); }
                                    if (k3[i] == 5) { draw(renderer, point5Texture, cube2); }
                                    if (k3[i] == 6) { draw(renderer, point6Texture, cube2); }
                                }
                                if (i == 1) {
                                    if (k3[i] == 1) { draw(renderer, point1Texture, cube3); }
                                    if (k3[i] == 2) { draw(renderer, point2Texture, cube3); }
                                    if (k3[i] == 3) { draw(renderer, point3Texture, cube3); }
                                    if (k3[i] == 4) { draw(renderer, point4Texture, cube3); }
                                    if (k3[i] == 5) { draw(renderer, point5Texture, cube3); }
                                    if (k3[i] == 6) { draw(renderer, point6Texture, cube3); }
                                }
                                if (i == 2) {
                                    if (k3[i] == 1) { draw(renderer, point1Texture, cube4); }
                                    if (k3[i] == 2) { draw(renderer, point2Texture, cube4); }
                                    if (k3[i] == 3) { draw(renderer, point3Texture, cube4); }
                                    if (k3[i] == 4) { draw(renderer, point4Texture, cube4); }
                                    if (k3[i] == 5) { draw(renderer, point5Texture, cube4); }
                                    if (k3[i] == 6) { draw(renderer, point6Texture, cube4); }
                                }
                            }

                            if (cnt_kub3(k3) == 0) {
                                sum += kub3(k3);
                                if (sum < 50) { cur_brosok = kubik5; }
                                else {
                                    if (firstPlayer == 1) { score1 += sum; }
                                    if (firstPlayer == 2) { score2 += sum; }
                                }
                            }
                            if (cnt_kub3(k3) == 1) {
                                sum += kub3(k3);
                                if (sum < 50) { cur_brosok = kubik1; }
                                else {
                                    if (firstPlayer == 1) { score1 += sum; }
                                    if (firstPlayer == 2) { score2 += sum; }
                                }
                            }
                            if (cnt_kub3(k3) == 2) {
                                sum += kub3(k3);
                                if (sum < 50) { cur_brosok = kubik2; }
                                else {
                                    if (firstPlayer == 1) { score1 += sum; }
                                    if (firstPlayer == 2) { score2 += sum; }
                                }
                            }
                            if (cnt_kub3(k3) == 3) {
                                sum = 0;
                                SDL_RenderPresent(renderer);
                                SDL_Delay(1500);
                                if (firstPlayer == 1) { firstPlayer = 2;  currentState = PLAYER2; break; }
                                if (firstPlayer == 2) { firstPlayer = 1;  currentState = PLAYER1; break; }
                            }
                            SDL_RenderPresent(renderer);
                            //SDL_Delay(2000);
                            //SDL_RenderPresent(renderer);
                        }
                        break;
                    case kubik2:
                        SDL_GetMouseState(&x, &y);
                        if (isHit(x, y, brosok)) {
                            //SDL_RenderPresent(renderer);
                            draw(renderer, mainGameTexture, bonusGame);
                            cnt1 = 0, cnt2 = 0, cnt3 = 0, cnt4 = 0, cnt5 = 0, cnt6 = 0;
                            for (int i = 0; i < 2; i++) {
                                k2[i] = rand() % 6 + 1;
                                //printf("%d  ", k2[i]);
                            }

                            for (int i = 0; i < 2; i++) {
                                if (i == 0) {
                                    if (k2[i] == 1) { draw(renderer, point1Texture, cube2); }
                                    if (k2[i] == 2) { draw(renderer, point2Texture, cube2); }
                                    if (k2[i] == 3) { draw(renderer, point3Texture, cube2); }
                                    if (k2[i] == 4) { draw(renderer, point4Texture, cube2); }
                                    if (k2[i] == 5) { draw(renderer, point5Texture, cube2); }
                                    if (k2[i] == 6) { draw(renderer, point6Texture, cube2); }
                                }
                                if (i == 1) {
                                    if (k2[i] == 1) { draw(renderer, point1Texture, cube3); }
                                    if (k2[i] == 2) { draw(renderer, point2Texture, cube3); }
                                    if (k2[i] == 3) { draw(renderer, point3Texture, cube3); }
                                    if (k2[i] == 4) { draw(renderer, point4Texture, cube3); }
                                    if (k2[i] == 5) { draw(renderer, point5Texture, cube3); }
                                    if (k2[i] == 6) { draw(renderer, point6Texture, cube3); }
                                }
                            }

                            if (cnt_kub2(k2) == 0) {
                                sum += kub2(k2);
                                if (sum < 50) { cur_brosok = kubik5; }
                                else {
                                    if (firstPlayer == 1) { score1 += sum; }
                                    if (firstPlayer == 2) { score2 += sum; }
                                }
                            }
                            if (cnt_kub2(k2) == 1) {
                                sum += kub2(k2);
                                if (sum < 50) { cur_brosok = kubik1; }
                                else {
                                    if (firstPlayer == 1) { score1 += sum; }
                                    if (firstPlayer == 2) { score2 += sum; }
                                }
                            }
                            if (cnt_kub2(k2) == 2) {
                                sum = 0;
                                SDL_RenderPresent(renderer);
                                SDL_Delay(1500);
                                if (firstPlayer == 1) { firstPlayer = 2;  currentState = PLAYER2; break; }
                                if (firstPlayer == 2) { firstPlayer = 1;  currentState = PLAYER1; break; }
                            }
                            SDL_RenderPresent(renderer);
                            //SDL_Delay(2000);
                            //SDL_RenderPresent(renderer);
                        }
                        break;
                    case kubik1:
                        SDL_GetMouseState(&x, &y);
                        if (isHit(x, y, brosok)) {
                            //SDL_RenderPresent(renderer);
                            draw(renderer, mainGameTexture, bonusGame);
                            cnt1 = 0, cnt2 = 0, cnt3 = 0, cnt4 = 0, cnt5 = 0, cnt6 = 0;
                            k1 = rand() % 6 + 1;
                            //printf("%d  ", k1);

                            if (k1 == 1) { draw(renderer, point1Texture, cube2); }
                            if (k1 == 2) { draw(renderer, point2Texture, cube2); }
                            if (k1 == 3) { draw(renderer, point3Texture, cube2); }
                            if (k1 == 4) { draw(renderer, point4Texture, cube2); }
                            if (k1 == 5) { draw(renderer, point5Texture, cube2); }
                            if (k1 == 6) { draw(renderer, point6Texture, cube2); }

                            if (cnt_kub1(k1) == 0) {
                                sum += kub1(k1);
                                if (sum < 50) { cur_brosok = kubik5; }
                                else {
                                    if (firstPlayer == 1) { score1 += sum; }
                                    if (firstPlayer == 2) { score2 += sum; }
                                }
                            }
                            if (cnt_kub1(k1) == 1) {
                                sum = 0;
                                SDL_RenderPresent(renderer);
                                SDL_Delay(1500);
                                if (firstPlayer == 1) { firstPlayer = 2;  currentState = PLAYER2; break; }
                                if (firstPlayer == 2) { firstPlayer = 1;  currentState = PLAYER1; break; }

                            }
                            SDL_RenderPresent(renderer);
                            //SDL_Delay(2000);
                        }
                        break;
                    }
                }
            }
            break;

            case COMBINATIONS:
                draw(renderer, combinationsTexture, bonusGame);
                if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT) {
                    SDL_GetMouseState(&x, &y);
                    if (isHit(x, y, Quit))
                    {
                        if (currentPrev == MAIN_GAME) {
                            currentState = MAIN_GAME;
                        }
                        else { currentState = MENU; }
                        break;
                    }
                    if (isHit(x, y, Rules)) {
                        currentState = RULES;
                        break;
                    }
                    if (isHit(x, y, Settings)) {
                        currentPrev = MAIN_GAME;
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
                    if (isHit(x, y, Settings)) {
                        draw(renderer, NKTexture, Settings);
                        break;
                    }
                    if (isHit(x, y, Rules)) {
                        draw(renderer, RuleTexture, Rules);
                        break;
                    }
                }
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
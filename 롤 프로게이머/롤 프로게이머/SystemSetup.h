#pragma once
#include "SDL.h"
#include "SDL_ttf.h"
#include "SDL_image.h"

//키보드 입력용
#define enterKey 1
#define escKey 0
#define upKey 8
#define downKey 2
#define leftKey 4
#define rightKey 6

//SDL 시작
void initializingSDL();

//SDL 종료
void endingSDL();

//Show Text
void Showtext(SDL_Renderer* renderer, int x_font, int y_font, int fontWidth, int fontHeight, const char* a);

//Show Text
void Shownum(SDL_Renderer* renderer, int x_font, int y_font, int fontWidth, int fontHeight, int i);

//Show Image
void bringImage(SDL_Renderer* renderer, int x_font, int y_font, int fontWidth, int fontHeight, const char* imagename);

//Hold Frame
bool holdFrame(int* holder, unsigned long long numFrame, int frameLength, int holdPosition);

//키보드 입력감지
int keyInput(SDL_Event event);

//타이틀
void title(SDL_Renderer* renderer);

//로비
int Lobby(SDL_Renderer* renderer);
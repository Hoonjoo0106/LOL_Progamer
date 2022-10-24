#pragma once
#include "SDL.h"
#include "SDL_ttf.h"
#include "SDL_image.h"

//Ű���� �Է¿�
#define enterKey 1
#define escKey 0
#define upKey 8
#define downKey 2
#define leftKey 4
#define rightKey 6

//SDL ����
void initializingSDL();

//SDL ����
void endingSDL();

//Show Text
void Showtext(SDL_Renderer* renderer, int x_font, int y_font, int fontWidth, int fontHeight, const char* a);

//Show Text
void Shownum(SDL_Renderer* renderer, int x_font, int y_font, int fontWidth, int fontHeight, int i);

//Show Image
void bringImage(SDL_Renderer* renderer, int x_font, int y_font, int fontWidth, int fontHeight, const char* imagename);

//Hold Frame
bool holdFrame(int* holder, unsigned long long numFrame, int frameLength, int holdPosition);

//Ű���� �Է°���
int keyInput(SDL_Event event);

//Ÿ��Ʋ
void title(SDL_Renderer* renderer);

//�κ�
int Lobby(SDL_Renderer* renderer);
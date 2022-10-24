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

//내 라인
void myLane(SDL_Renderer* renderer);

//프레임 표기
void frameUpdate(SDL_Renderer* renderer, int* myHP, int* opHP, int myDamage, int opDamage, int* x_arrow, int* announcement,
	int turn, unsigned long long numFrame, int *holder, int* showmyDamage, int* showopDamage);

//라인전 전투
void laneCombat(SDL_Renderer* renderer, int laneMove, int oppoMove, 
	int* myHP, int* opHP, int* myDamage, int* opDamage, int* announcement);

//라인전 선택
void moveSelect(SDL_Renderer* renderer, int* x_arrow, int* arrowLocation, int* laneMove, bool* enterPress);
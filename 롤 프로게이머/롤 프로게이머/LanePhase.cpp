#include <iostream>
#include <stdlib.h>
#include <time.h>


#include "SDL.h"
#include "SDL_ttf.h"
#include "SDL_image.h"


#include "SystemSetup.h"
#include "LanePhase.h"

using namespace std;


//내 라인
void myLane(SDL_Renderer* renderer) {
    SDL_Event event;
    //랜덤 가동
    srand(time(NULL));


    //협곡 입장
    bringImage(renderer, 0, 0, 1920, 1080, "Summoner's_Rift.jpg");
    Showtext(renderer, 535, 200, 850, 100, "Welcome to the Summor's Rift");
    SDL_RenderPresent(renderer);
    //SDL_Delay(2000);

    //챔피언 스텟
    int myHP = 100;
    int opHP = 100;

    //변수 생성
    //
    //프레임 수
    unsigned long long numFrame = 1;
    //Kill anounce(0), Death annouce(1), myDamage(2), opDamage(3)
    int holder[] = { 0,0,0,0 };

    //라인전선택
    int laneMove = 0;
    //화살표 위치 시작부분
    int arrowLocation = 0;
    int x_arrow = 310;

    //announce
    int announcement = 0;

    //턴#
    unsigned int turn = 1;

    //데미지 표시 저장
    int showmyDamage = 0;
    int showopDamage = 0;
    

    while (1) {
        //엔터키 인식
        bool enterPress = false;

        //데미지
        int myDamage = 0;
        int opDamage = 0;

        //적 선택
        int oppoMove = rand() % 3;

        //내 선택
        moveSelect(renderer, &x_arrow, &arrowLocation, &laneMove, &enterPress);
        if (enterPress == true) {
            laneCombat(renderer, laneMove, oppoMove, &myHP, &opHP, &myDamage, &opDamage, &announcement);
            turn++;
        }
        //킬 데스등 Announcement 출력
        //+언제까지 띄우고 언제 지울지

        //HP등 현 스텟 출력

        //프레임 최신화
        frameUpdate(renderer, &myHP, &opHP, myDamage, opDamage, &x_arrow, &announcement, turn, numFrame, holder,
            &showmyDamage, &showopDamage);
        numFrame++;
    }
}


//프레임에 표기
void frameUpdate(SDL_Renderer* renderer, int* myHP, int* opHP, int myDamage, int opDamage, int* x_arrow, int* announcement,
    int turn, unsigned long long numFrame, int* holder, int* showmyDamage, int* showopDamage) {
    SDL_Event event;
    //화살표 위치
    
    //로비 배경
    bringImage(renderer, 0, 0, 1920, 1080, "Summoner's_Rift.jpg");
    Showtext(renderer, 760, 710, 400, 70, "Choose your move");
    Showtext(renderer, 365, 850, 150, 40, "Attack");
    Showtext(renderer, 900, 850, 120, 40, "Farm");
    Showtext(renderer, 1400, 850, 130, 40, "Avoid");
    Showtext(renderer, 1500, 160, 120, 40, "Turn:");
    Shownum(renderer, 1630, 160, 50, 40, turn);


    //Health Bar
    bringImage(renderer, 245, 400, 210, 100, "Healthbar_grey.png");
    bringImage(renderer, 250, 433, (2 * (*myHP)), 33, "Healthbar_green.png");
    bringImage(renderer, 245, 400, 210, 100, "Healthbar_edge.png");
    Shownum(renderer, 275, 440, 50, 20, *myHP); Showtext(renderer, 340, 440, 20, 20, "/"); Shownum(renderer, 370, 440, 50, 20, 100);

    //opponent Health Bar
    bringImage(renderer, 1465, 400, 210, 100, "Healthbar_grey.png");
    bringImage(renderer, 1470, 433, (2 * (*opHP)), 33, "Healthbar_green.png");
    bringImage(renderer, 1465, 400, 210, 100, "Healthbar_edge.png");
    Shownum(renderer, 1495, 440, 50, 20, *opHP); Showtext(renderer, 1560, 440, 20, 20, "/"); Shownum(renderer, 1590, 440, 50, 20, 100);
    
    //Announcement
    
    if (*announcement == 1) {
        if (holdFrame(holder, numFrame, 20, 0) == 1) {
            Showtext(renderer, 535, 200, 850, 100, "You have Slain an Enemy");
        }
        else {
            *announcement = 0;
        }
    }
    else if (*announcement == 2) {
        if (holdFrame(holder, numFrame, 20, 1) == 1) {
            Showtext(renderer, 535, 200, 850, 100, "You have been Slain");
        }
        else {
            *announcement = 0;
        }
    }
    
    
    //Change in HP
    if (myDamage != 0 || *showmyDamage != 0) {
        //데미지 저장(이렇게 안하고 바로 계산용 데미지를 넣으면 프레임마다 리셋되서 유지를 못한다
        if (*showmyDamage == 0) {
            *showmyDamage = myDamage;
        }
        //10프레임 표기
        if (holdFrame(holder, numFrame, 10,2) == 1) {
            Shownum(renderer, 350, 380, 50, 40, *showmyDamage);
        }
        else {
            *showmyDamage = 0;
        }
    }
    if (opDamage != 0 || *showopDamage != 0) {
        //데미지 저장(이렇게 안하고 바로 계산용 데미지를 넣으면 프레임마다 리셋되서 유지를 못한다
        if (*showopDamage == 0) {
            *showopDamage = opDamage;
        }
        //10프레임 표기
        if (holdFrame(holder, numFrame, 10,3) == 1) {
            Shownum(renderer, 1550, 380, 50, 40, *showopDamage);
        }
        else {
            *showopDamage = 0;
        }
    }


    //화살표
    bringImage(renderer, *x_arrow, 851, 65, 40, "white-arrow.png");

    SDL_RenderPresent(renderer);
}


//라인전 전투
void laneCombat(SDL_Renderer* renderer, int laneMove, int oppoMove,
    int* myHP, int* opHP, int* myDamage, int* opDamage, int* announcement) {
    //공격
    if (laneMove == 0) {
        if (oppoMove == 0) {
            *myDamage = -20;
            *opDamage = -20;
            *myHP += *myDamage;
            *opHP += *opDamage;
        }
        else if (oppoMove == 1) {
            *opDamage = -30;
            *opHP += *opDamage;
        }
        else {

        }
    }

    //파밍
    else if (laneMove == 1) {
        if (oppoMove == 0) {
            *myDamage = -30;
            *myHP += *myDamage;
        }
        else if (oppoMove == 1) {

        }
        else {
            *myDamage = 10;
            *myHP += *myDamage;
        }
    }

    //회피
    else if (laneMove == 2) {
        if (oppoMove == 0) {

        }
        else if (oppoMove == 1) {
            *opDamage = 10;
            *opHP += *opDamage;
        }
        else {

        }
    }
    //킬 여부
    if (*myHP <= 0) {
        *announcement = 2;
    }
    else if (*opHP <= 0) {
        *announcement = 1;
    }
}


//라인전 선택
void moveSelect(SDL_Renderer* renderer, int* x_arrow, int* arrowLocation, int* laneMove, bool* enterPress) {
    SDL_Event event;
    //화살표 위치
    

    while (1) {
        //키보드 입력
        if (SDL_PollEvent(&event)) {
            if (keyInput(event) == leftKey) {
                *arrowLocation -= 1;
            }
            else if (keyInput(event) == rightKey) {
                *arrowLocation += 1;
            }
            else if (keyInput(event) == enterKey) {
                *laneMove = *arrowLocation % 3;
                *enterPress = true;
            }
        }
        if (*arrowLocation % 3 == 0) {
            *x_arrow = 310;
            break;
        }
        else if (*arrowLocation % 3 == 1) {
            *x_arrow = 845;
            break;
        }
        else {
            *x_arrow = 1345;
            break;
        }
    }
}

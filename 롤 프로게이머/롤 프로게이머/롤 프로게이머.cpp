#include <iostream>

//SDL 그래픽 헤더파일들
#include "SDL.h"
#include "SDL_ttf.h"
#include "SDL_image.h"

//수제 파일들
#include "SystemSetup.h"
#include "LanePhase.h"

using namespace std;




int main(int argc, char* argv[]) {
    //SDL 시작
    initializingSDL();

    //팝업 윈도우 설정/생성
    SDL_Window* window = SDL_CreateWindow("LOL Progamer", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1920, 1080, SDL_WINDOW_SHOWN);
    //해당 윈도우에 랜더러 생성
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);
    //Set the color of renderer(Background)
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    //Make the entire screen into SetRenderDrawColor
    SDL_RenderClear(renderer);
    //Setup for input
    SDL_Event event;
    


    //시작 타이틀
Title:

    title(renderer);

    bool gamerun = 1;
    while (gamerun) {
        //키 입력
        if (SDL_PollEvent(&event)) {
            if (keyInput(event) == enterKey) {
                int gamemode = Lobby(renderer);
                if (gamemode == 0) {
                    myLane(renderer);
                }
                else if (gamemode == 1) {

                }
                else if (gamemode == 2) {

                }
                else if (gamemode == -1) {
                    goto Title;
                }
            }
            else if (keyInput(event) == escKey) {
                gamerun = false;
            }
        }
    }


    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    //SDL 종료
    endingSDL();
    return 0;
}






//단축시 모음
//지정한 구문 주석: Ctrl + k,c(컨트롤 누른 상태로 k 한번 누르고 c 한번 누르고)
//지정한 구문 주석 해제: Ctrl + k,u
//되돌리기: Ctrl + z
//자르기: Ctrl + x
//무한루프 탈출: Ctrl + c
//Alt drag(구문 세로로 드래그하기)
//중단점 생산 및 해제: F9 (중단점을 생성하면 그 라인의 코드가 실행되기 직전에 중단한다)
//디버깅 중 구문 수행(한줄을 수행한다): F10
//디버깅 중 구문 수행(한줄에서도 한 명령을 하나하나 수행한다. ex +-*/, 여러함수중 하나 수행): F11
//다른파일에 있는 함수 찾기: F12
//디버깅 중 종료: Shift + F5
//중단점을 2개하면 그 사이부분이 무시된다
//함수 선언 확인: 함수관호안에서 Ctrl + Shift + Space
//


// 프로그램 실행: <Ctrl+F5> 또는 [디버그] > [디버깅하지 않고 시작] 메뉴
// 프로그램 디버그: <F5> 키 또는 [디버그] > [디버깅 시작] 메뉴

// 시작을 위한 팁: 
//   1. [솔루션 탐색기] 창을 사용하여 파일을 추가/관리합니다.
//   2. [팀 탐색기] 창을 사용하여 소스 제어에 연결합니다.
//   3. [출력] 창을 사용하여 빌드 출력 및 기타 메시지를 확인합니다.
//   4. [오류 목록] 창을 사용하여 오류를 봅니다.
//   5. [프로젝트] > [새 항목 추가]로 이동하여 새 코드 파일을 만들거나, [프로젝트] > [기존 항목 추가]로 이동하여 기존 코드 파일을 프로젝트에 추가합니다.
//   6. 나중에 이 프로젝트를 다시 열려면 [파일] > [열기] > [프로젝트]로 이동하고 .sln 파일을 선택합니다.

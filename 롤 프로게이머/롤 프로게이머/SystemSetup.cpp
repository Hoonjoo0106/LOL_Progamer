#include <iostream>
#include <sstream>
using namespace std;
#include "SystemSetup.h"

#include "SDL.h"
#include "SDL_ttf.h"
#include "SDL_image.h"


//SDL 시작
void initializingSDL() {
    SDL_Init(SDL_INIT_EVERYTHING);
    TTF_Init();
    IMG_Init(IMG_INIT_JPG || IMG_INIT_PNG);
}


//SDL 종료
void endingSDL() {
    IMG_Quit();
    TTF_Quit();
    SDL_Quit();
}


//Show Text
void Showtext(SDL_Renderer* renderer, int x_font, int y_font, int fontWidth, int fontHeight, const char* a) {
    //TEXT
    // 
    //Set up Font Type and Size
    TTF_Font* font = TTF_OpenFont("arial.ttf", 25);
    SDL_Color fontColor = { 255, 255, 255 };

    //create surface
    SDL_Surface* surfaceMessage = TTF_RenderText_Solid(font, a, fontColor);
    //convert to texture
    SDL_Texture* textureMessage = SDL_CreateTextureFromSurface(renderer, surfaceMessage);

    SDL_Rect Message_rect; //create a rect
    Message_rect.x = x_font;  //controls the rect's x coordinate 
    Message_rect.y = y_font; // controls the rect's y coordinte
    Message_rect.w = fontWidth; // controls the width of the rect
    Message_rect.h = fontHeight; // controls the height of the rect

    // TIP:
    //
    // (0,0) is on the top left of the window/screen,
    // think a rect as the text's box,
    // that way it would be very simple to understand

    // Now since it's a texture, you have to put RenderCopy
    // in your game loop area, the area where the whole code executes

    // you put the renderer's name first, the Message,
    // the crop size (you can ignore this if you don't want
    // to dabble with cropping), and the rect which is the size
    // and coordinate of your texture

    //text 저장
    SDL_RenderCopy(renderer, textureMessage, NULL, &Message_rect);

    //free sruface and texture
    SDL_FreeSurface(surfaceMessage);
    SDL_DestroyTexture(textureMessage);
}

//Show Number
void Shownum(SDL_Renderer* renderer, int x_font, int y_font, int fontWidth, int fontHeight, int i) {
    //Number
    // 
    //Set up Font Type and Size
    TTF_Font* font = TTF_OpenFont("arial.ttf", 25);
    SDL_Color fontColor = { 255, 255, 255 };

    //switch integer to string
    stringstream ss;
    ss << i;
    string num;
    ss >> num;
    
    //create surface
    SDL_Surface* surfaceMessage = TTF_RenderText_Solid(font, num.c_str(), fontColor);
    //convert to texture
    SDL_Texture* textureMessage = SDL_CreateTextureFromSurface(renderer, surfaceMessage);

    SDL_Rect Message_rect; //create a rect
    Message_rect.x = x_font;  //controls the rect's x coordinate 
    Message_rect.y = y_font; // controls the rect's y coordinte
    Message_rect.w = fontWidth; // controls the width of the rect
    Message_rect.h = fontHeight; // controls the height of the rect

    // TIP:
    //
    // (0,0) is on the top left of the window/screen,
    // think a rect as the text's box,
    // that way it would be very simple to understand

    // Now since it's a texture, you have to put RenderCopy
    // in your game loop area, the area where the whole code executes

    // you put the renderer's name first, the Message,
    // the crop size (you can ignore this if you don't want
    // to dabble with cropping), and the rect which is the size
    // and coordinate of your texture

    //text 저장
    SDL_RenderCopy(renderer, textureMessage, NULL, &Message_rect);

    //free sruface and texture
    SDL_FreeSurface(surfaceMessage);
    SDL_DestroyTexture(textureMessage);
}


//Show Image
void bringImage(SDL_Renderer* renderer, int x_font, int y_font, int fontWidth, int fontHeight, const char* imagename) {
    //IMAGE
    //
    //create surface
    SDL_Surface* surfaceImage = IMG_Load(imagename);
    //convert to texture
    SDL_Texture* textureImage = SDL_CreateTextureFromSurface(renderer, surfaceImage);

    SDL_Rect Message_rect; //create a rect
    Message_rect.x = x_font;  //controls the rect's x coordinate 
    Message_rect.y = y_font; // controls the rect's y coordinte
    Message_rect.w = fontWidth; // controls the width of the rect
    Message_rect.h = fontHeight; // controls the height of the rect

    // TIP:
    //
    // (0,0) is on the top left of the window/screen,
    // think a rect as the text's box,
    // that way it would be very simple to understand

    // Now since it's a texture, you have to put RenderCopy
    // in your game loop area, the area where the whole code executes

    // you put the renderer's name first, the Message,
    // the crop size (you can ignore this if you don't want
    // to dabble with cropping), and the rect which is the size
    // and coordinate of your texture

    //text 저장
    SDL_RenderCopy(renderer, textureImage, NULL, &Message_rect);

    //free sruface and texture
    SDL_FreeSurface(surfaceImage);
    SDL_DestroyTexture(textureImage);
}

//Hold Frame for "frameLength" frames
bool holdFrame(int* holder, unsigned long long numFrame, int frameLength, int holdPosition) {
    if (holder[holdPosition] == 0) {
        holder[holdPosition] = numFrame;
        return 1;
    }
    //표기
    else if (holder[holdPosition] + frameLength >= numFrame) {
        return 1;
    }
    //표기 해제
    else{
        holder[holdPosition] = 0;
        return 0;
    }
}





//키보드 입력감지
int keyInput(SDL_Event event) {
    if (event.type == SDL_KEYUP) {
        if (event.key.keysym.sym == SDLK_KP_ENTER || event.key.keysym.sym == SDLK_RETURN) {
            return 1;
        }
        else if (event.key.keysym.sym == SDLK_ESCAPE) {
            return 0;
        }
        else if (event.key.keysym.sym == SDLK_UP) {
            return 8;
        }
        else if (event.key.keysym.sym == SDLK_DOWN) {
            return 2;
        }
        else if (event.key.keysym.sym == SDLK_LEFT) {
            return 4;
        }
        else if (event.key.keysym.sym == SDLK_RIGHT) {
            return 6;
        }
    }
}


//타이틀
void title(SDL_Renderer* renderer) {
    bringImage(renderer, 0, 0, 1920, 1080, "Title.jpg");
    SDL_RenderPresent(renderer);
    //SDL_Delay(1000);

    Showtext(renderer, 630, 730, 660, 100, "Welcome to LOL progamer");
    SDL_RenderPresent(renderer);
    //SDL_Delay(2000);

    Showtext(renderer, 1460, 870, 250, 40, "Press Enter to Play");
    Showtext(renderer, 1460, 915, 235, 40, "Press ESC to Exit");
    SDL_RenderPresent(renderer);
    //SDL_Delay(1000);
}


//로비
int Lobby(SDL_Renderer* renderer) {
    SDL_Event event;
    
    //화살표 위치값
    int arrowLocation = 0;
    int x_arrow = 310;
    while (1) {
        //로비 배경
        bringImage(renderer, 0, 0, 1920, 1080, "Title.jpg");
        Showtext(renderer, 735, 690, 450, 70, "Select Game Mode");
        Showtext(renderer, 365, 810, 270, 50, "Ranked");
        Showtext(renderer, 810, 810, 300, 50, "Scrimmage");
        Showtext(renderer, 1275, 810, 330, 50, "Professional");
        Showtext(renderer, 1390, 915, 320, 40, "Press ESC to return to title");

        //화살표 시작지점
        bringImage(renderer, x_arrow, 817, 65, 40, "white-arrow.png");
        SDL_RenderPresent(renderer);
        if (SDL_PollEvent(&event)){
            if (keyInput(event) == leftKey) {
                arrowLocation -= 1;
            }
            else if (keyInput(event) == rightKey) {
                arrowLocation += 1;
            }
            else if (keyInput(event) == enterKey) {
                return arrowLocation % 3;
                break;
            }
            else if (keyInput(event) == escKey) {
                return -1;
                break;
            }
        }
        if (arrowLocation % 3 == 0) {
            x_arrow = 310;
        }
        else if (arrowLocation % 3 == 1) {
            x_arrow = 755;
        }
        else {
            x_arrow = 1220;
        }
    }
}
/****************************************************************
 *             -The Mane Menu Screen-
 *  All the logic for a Mane Menu of are game.
 *  Created by Squid on 10/27/2025.
****************************************************************/

#include "screens.h"
#include "../../include/UI/Buttons/buttons.h"


static GameScreen nextScreen;

UIButton startButton;
int strButtonX;
int strButtonY;
int strButtonWidth;
int strButtonHeight;


void InitMenuScreen(void) {

    strButtonWidth = 150;
    strButtonHeight = 60;
    strButtonX = (GetScreenWidth() - strButtonWidth) / 2;
    strButtonY =   300;

    nextScreen = SCREEN_MENU;
    InitUiButtons(&startButton, strButtonX, strButtonY,strButtonWidth, strButtonHeight, BLUE);
}

void UpdateMenuScreen(void)
{

}

void DrawMenuScreen(void)
{
    // Title
    const char* title = "Hyper Paddle";
    int titleFont = 40;
    int titleWidth = MeasureText(title, titleFont);
    DrawText(title, (GetScreenWidth() - titleWidth)/2, (int)((GetScreenHeight()/2.0f) - 120), titleFont, DARKGRAY);

    DrawUiButtons(&startButton,"BOB", 20);

}

void UnloadMenuScreen(void)
{
    // Nothing to unload yet
}

GameScreen FinishMenuScreen(void)
{
    return nextScreen;
}
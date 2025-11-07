/****************************************************************
 *             - The Mane Menu Screen -
 *  All the logic for a Mane Menu of are game.
 *  Created by Squid on 10/27/2025.
****************************************************************/

#include "screens.h"
#include "../../include/UI/UIButton/button.h"

extern bool gameShouldClose;
static GameScreen nextScreen;

UIButton startButton;
int strButtonX;
int strButtonY;
int strButtonWidth;
int strButtonHeight;

UIButton quitButton;
int quitButtonX;
int quitButtonY;
int quitButtonWidth;
int quitButtonHeight;

int titleFontSize;

void InitMenuScreen(void) {
    titleFontSize = 80;

    // Start Button values
    strButtonWidth = 150;
    strButtonHeight = 60;
    strButtonX = (GetScreenWidth() - strButtonWidth) / 2;
    strButtonY = (GetScreenHeight() - strButtonHeight) / 2 + titleFontSize - 50;

    // Values for a quit button
    quitButtonWidth = 150;
    quitButtonHeight = 60;
    quitButtonX = (GetScreenWidth() - quitButtonWidth) / 2;
    quitButtonY = (GetScreenHeight() - quitButtonHeight) / 2 + titleFontSize + 70;

    nextScreen = SCREEN_MENU;

    // Start Button
    InitUiButton(&startButton, (float)strButtonX,
                 (float)strButtonY, (float)strButtonWidth,
                 (float)strButtonHeight, BLUE, DARKBLUE,
                 SKYBLUE, BLACK);
    //Quit Button
    InitUiButton(&quitButton, (float)quitButtonX, (float)quitButtonY,
        (float)quitButtonWidth, (float)quitButtonHeight,
        RED, DARKPURPLE, SKYBLUE, BLACK);
}

void UpdateMenuScreen(void) {
    UpdateUiButton(&startButton);
    UpdateUiButton(&quitButton);

    if (IsUiButtonClicked(&startButton)) {
        // TODO have the start button go to the game screen.
        nextScreen = SCREEN_MAIN_GAME;
    }

    if (IsUiButtonClicked(&quitButton)) {
        // close the window and unload assets
        gameShouldClose = true;
    }
}

void DrawMenuScreen(void) {
    ClearBackground(BLACK);

    // Title
    //********************************************************
    const char *title = "Hyper Paddle";
    int titleFont = titleFontSize;
    int titleWidth = MeasureText(title, titleFont);
    DrawText(title,
             (GetScreenWidth() - titleWidth) / 2,
             ((int) (GetScreenHeight() / (int) 2.0f) - 120),
             titleFont, DARKGRAY);
    //********************************************************

    // Draw the Start Button.
    DrawUiButton(&startButton, "Start", 40);
    DrawUiButton(&quitButton, "Quit", 40);
}

void UnloadMenuScreen(void) {
    // Nothing to unload yet
}

GameScreen FinishMenuScreen(void) {
    return nextScreen;
}
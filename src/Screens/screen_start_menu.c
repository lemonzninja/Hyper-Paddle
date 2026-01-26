/****************************************************************
 *             - The Main Menu Screen -
 *  All the logic for a Main Menu of our game.
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

int btnTextSize;
int titleFontSize;

int buttonHeight;
int buttonWidth;

void InitMenuScreen(void) {
    titleFontSize = 90;
    btnTextSize = 30;
    buttonHeight = 50;
    buttonWidth = 100;

    // Start Button values
    strButtonWidth = buttonWidth;
    strButtonHeight = buttonHeight;
    strButtonX = (GetScreenWidth() - strButtonWidth) / 2;
    strButtonY = (GetScreenHeight() - strButtonHeight) / 2 + titleFontSize - 50;

    // Values for a quit button
    quitButtonWidth = buttonWidth;
    quitButtonHeight = buttonHeight;
    quitButtonX = (GetScreenWidth() - quitButtonWidth) / 2;
    quitButtonY = (GetScreenHeight() - quitButtonHeight) / 2 + titleFontSize + 120;

    nextScreen = SCREEN_MENU;

    // Start Button
    InitUiButton(&startButton, (float)strButtonX,
                 (float)strButtonY, (float)strButtonWidth,
                 (float)strButtonHeight, BLUE, DARKBLUE,
                 SKYBLUE, LIGHTGRAY);
    //Quit Button
    InitUiButton(&quitButton, (float)quitButtonX, (float)quitButtonY,
        (float)quitButtonWidth, (float)quitButtonHeight,
        RED, DARKPURPLE, SKYBLUE, BLACK);
}

void UpdateMenuScreen(void) {
    UpdateUiButton(&startButton);
    UpdateUiButton(&quitButton);

    if (IsUiButtonClicked(&startButton)) {
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
    const int titleFont = titleFontSize;
    const int titleWidth = MeasureText(title, titleFont);
    DrawText(title,
             (GetScreenWidth() - titleWidth) / 2,
             ((int) (GetScreenHeight() / (int) 2.0f) - 120),
             titleFont, DARKGRAY);
    //********************************************************

    // Draw the Start Button.
    DrawUiButton(&startButton, "Start", btnTextSize);
    DrawUiButton(&quitButton, "Quit", btnTextSize);
}

void UnloadMenuScreen(void) {
    // Nothing to unload yet
}

GameScreen GetMainGameScreen(void) {
    return nextScreen;
}
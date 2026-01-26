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

UIButton menuButton;
int menuButtonX;
int menuButtonY;
int menuButtonWidth;
int menuButtonHeight;

UIButton quitButton;
int quitButtonX;
int quitButtonY;
int quitButtonWidth;
int quitButtonHeight;

int btnTextSize;
int titleFontSize;

int buttonHeight;
int buttonWidth;
int buttonSpacing;

void InitMenuScreen(void) {
    titleFontSize = 90;
    btnTextSize = 30;
    buttonHeight = 50;
    buttonWidth = 100;
    buttonSpacing = 85;

    // Start Button values
    strButtonWidth = buttonWidth;
    strButtonHeight = buttonHeight;
    strButtonX = (GetScreenWidth() - strButtonWidth) / 2;
    strButtonY = (GetScreenHeight() - strButtonHeight) / 2 + titleFontSize - 50;

    // Values for a menu button
    menuButtonWidth = buttonWidth;
    menuButtonHeight = buttonHeight;
    menuButtonX = (GetScreenWidth() - menuButtonWidth) / 2;
    menuButtonY = strButtonY + buttonSpacing;

    // Values for a quit button
    quitButtonWidth = buttonWidth;
    quitButtonHeight = buttonHeight;
    quitButtonX = (GetScreenWidth() - quitButtonWidth) / 2;
    quitButtonY = strButtonY + (buttonSpacing * 2);

    nextScreen = SCREEN_MENU;

    // Start Button
    InitUiButton(&startButton, (float)strButtonX,
                 (float)strButtonY, (float)strButtonWidth,
                 (float)strButtonHeight, BLUE, DARKBLUE,
                 SKYBLUE, LIGHTGRAY);
    // Menu Button
    InitUiButton(&menuButton, (float)menuButtonX, (float)menuButtonY,
                 (float)menuButtonWidth, (float)menuButtonHeight,
                 DARKGREEN, GREEN, SKYBLUE, BLACK);
    //Quit Button
    InitUiButton(&quitButton, (float)quitButtonX, (float)quitButtonY,
        (float)quitButtonWidth, (float)quitButtonHeight,
        RED, DARKPURPLE, SKYBLUE, BLACK);
}

void UpdateMenuScreen(void) {
    UpdateUiButton(&startButton);
    UpdateUiButton(&menuButton);
    UpdateUiButton(&quitButton);

    if (IsUiButtonClicked(&startButton)) {
        nextScreen = SCREEN_MAIN_GAME;
    }

    if (IsUiButtonClicked(&menuButton)) {
        nextScreen = SCREEN_SETTINGS;
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
    DrawUiButton(&menuButton, "Menu", btnTextSize);
    DrawUiButton(&quitButton, "Quit", btnTextSize);
}

void UnloadMenuScreen(void) {
    // Nothing to unload yet
}

GameScreen GetMainGameScreen(void) {
    return nextScreen;
}
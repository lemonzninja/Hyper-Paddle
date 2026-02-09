/****************************************************************
 *             - The Main Menu Screen -
 *  All the logic for a Main Menu of our game.
 *  Created by Squid on 10/27/2025.
 ****************************************************************/

#include "../../include/UI/UIButton/button.h"
#include "screens.h"

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
int titleWidth;
int titleHeight;
float titleScale;
Texture2D titleTexture;

int buttonHeight;
int buttonWidth;
int buttonSpacing;

void InitMenuScreen(void) {
    titleFontSize = 90;
    titleWidth = titleFontSize;
    titleHeight = titleFontSize;
    btnTextSize = 28;
    buttonHeight = 52;
    buttonWidth = 220;
    buttonSpacing = 74;

    titleTexture = LoadTexture("assets/Title/Game_title.png");
    if (titleTexture.id == 0) {
        TraceLog(LOG_WARNING, "SCREEN_MENU: Failed to load title texture");
    } else {
        float maxTitleWidth = GetScreenWidth() * 0.85f;
        float maxTitleHeight = GetScreenHeight() * 0.25f;
        float widthScale = maxTitleWidth / (float) titleTexture.width;
        float heightScale = maxTitleHeight / (float) titleTexture.height;

        titleScale = 1.0f;
        if (widthScale < titleScale) {
            titleScale = widthScale;
        }
        if (heightScale < titleScale) {
            titleScale = heightScale;
        }
        if (titleScale > 1.0f) {
            titleScale = 1.0f;
        }

        titleWidth = (int) (titleTexture.width * titleScale);
        titleHeight = (int) (titleTexture.height * titleScale);
    }

    // Start Button values
    strButtonWidth = buttonWidth;
    strButtonHeight = buttonHeight;
    strButtonX = (GetScreenWidth() - strButtonWidth) / 2;
    strButtonY = (GetScreenHeight() - strButtonHeight) / 2 + titleHeight - 50;

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
    InitUiButton(&startButton, (float) strButtonX, (float) strButtonY,
                 (float) strButtonWidth, (float) strButtonHeight,
                 (Color){100, 211, 20, 255},
                 (Color){134, 235, 44, 255},
                 (Color){73, 166, 13, 255},
                 (Color){21, 38, 40, 255});
    // Menu Button
    InitUiButton(&menuButton, (float) menuButtonX, (float) menuButtonY,
                 (float) menuButtonWidth, (float) menuButtonHeight,
                 (Color){253, 196, 35, 255},
                 (Color){255, 214, 71, 255},
                 (Color){214, 148, 16, 255},
                 (Color){33, 39, 39, 255});
    // Quit Button
    InitUiButton(&quitButton, (float) quitButtonX, (float) quitButtonY,
                 (float) quitButtonWidth, (float) quitButtonHeight,
                 (Color){252, 66, 108, 255},
                 (Color){255, 98, 136, 255},
                 (Color){206, 43, 85, 255},
                 (Color){37, 29, 34, 255});
}

void UpdateMenuScreen(void) {
    UpdateUiButton(&startButton);
    UpdateUiButton(&menuButton);
    UpdateUiButton(&quitButton);

    if (IsUiButtonClicked(&startButton)) {
        nextScreen = SCREEN_LEVEL_SELECT;
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
    if (titleTexture.id != 0) {
        int titleX = (GetScreenWidth() - titleWidth) / 2;
        int titleY = (GetScreenHeight() / 2) - 120;
        DrawTextureEx(titleTexture, (Vector2){(float) titleX, (float) titleY}, 0.0f,
                      titleScale, WHITE);
    } else {
        const char *title = "Hyper Paddle";
        const int titleFont = titleFontSize;
        const int textWidth = MeasureText(title, titleFont);
        DrawText(title, (GetScreenWidth() - textWidth) / 2,
                 ((int) (GetScreenHeight() / (int) 2.0f) - 120), titleFont, DARKGRAY);
    }
    //********************************************************

    // Draw the Start Button.
    DrawUiButton(&startButton, "START", btnTextSize);
    DrawUiButton(&menuButton, "MENU", btnTextSize);
    DrawUiButton(&quitButton, "QUIT", btnTextSize);
}

void UnloadMenuScreen(void) {
    if (titleTexture.id != 0) {
        UnloadTexture(titleTexture);
    }
}

GameScreen GetMainGameScreen(void) { return nextScreen; }

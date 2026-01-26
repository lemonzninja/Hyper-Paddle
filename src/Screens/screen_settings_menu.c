/****************************************************************
 *           - The Settings Screen -
 *  Options and configuration for the game.
 *  Created by Squid on 01/26/2026.
****************************************************************/

#include "screens.h"
#include "../../include/UI/UIButton/button.h"

static GameScreen nextScreen;

static UIButton backButton;
static int backButtonX;
static int backButtonY;
static int backButtonWidth;
static int backButtonHeight;

static int btnTextSize;
static int titleFontSize;

void InitSettingsScreen(void) {
    titleFontSize = 70;
    btnTextSize = 28;
    backButtonWidth = 140;
    backButtonHeight = 50;

    backButtonX = (GetScreenWidth() - backButtonWidth) / 2;
    backButtonY = (GetScreenHeight() - backButtonHeight) / 2 + 140;

    nextScreen = SCREEN_SETTINGS;

    InitUiButton(&backButton, (float)backButtonX, (float)backButtonY,
                 (float)backButtonWidth, (float)backButtonHeight,
                 DARKGREEN, GREEN, SKYBLUE, BLACK);
}

void UpdateSettingsScreen(void) {
    UpdateUiButton(&backButton);

    if (IsUiButtonClicked(&backButton)) {
        nextScreen = SCREEN_MENU;
    }
}

void DrawSettingsScreen(void) {
    ClearBackground(BLACK);

    const char *title = "Settings";
    const int titleWidth = MeasureText(title, titleFontSize);
    DrawText(title,
             (GetScreenWidth() - titleWidth) / 2,
             (GetScreenHeight() / 2) - 180,
             titleFontSize, DARKGRAY);

    DrawText("Options coming soon...",
             (GetScreenWidth() / 2) - 140,
             (GetScreenHeight() / 2) - 40,
             20, LIGHTGRAY);

    DrawUiButton(&backButton, "Back", btnTextSize);
}

void UnloadSettingsScreen(void) {
    // Nothing to unload yet
}

GameScreen GetSettingsScreen(void) {
    return nextScreen;
}

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
static Rectangle soundToggleBox;
static int soundToggleSize;
static int soundLabelX;
static int soundLabelY;
static bool soundEnabled = true;

static int btnTextSize;
static int titleFontSize;

void InitSettingsScreen(void) {
    titleFontSize = 70;
    btnTextSize = 28;
    backButtonWidth = 140;
    backButtonHeight = 50;
    soundToggleSize = 28;

    backButtonX = (GetScreenWidth() - backButtonWidth) / 2;
    backButtonY = (GetScreenHeight() - backButtonHeight) / 2 + 140;

    nextScreen = SCREEN_SETTINGS;

    InitUiButton(&backButton, (float)backButtonX, (float)backButtonY,
                 (float)backButtonWidth, (float)backButtonHeight,
                 DARKGREEN, GREEN, SKYBLUE, BLACK);

    const char *soundLabel = "Sound";
    const int soundLabelWidth = MeasureText(soundLabel, btnTextSize);
    const int toggleSpacing = 12;
    const int groupWidth = soundToggleSize + toggleSpacing + soundLabelWidth;
    const int groupX = (GetScreenWidth() - groupWidth) / 2;
    const int groupY = backButtonY - 90;

    soundToggleBox = (Rectangle){ (float)groupX, (float)groupY,
                                  (float)soundToggleSize, (float)soundToggleSize };
    soundLabelX = groupX + soundToggleSize + toggleSpacing;
    soundLabelY = groupY + (soundToggleSize - btnTextSize) / 2;
}

void UpdateSettingsScreen(void) {
    UpdateUiButton(&backButton);

    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) &&
        CheckCollisionPointRec(GetMousePosition(), soundToggleBox)) {
        soundEnabled = !soundEnabled;
        SetMasterVolume(soundEnabled ? 1.0f : 0.0f);
    }

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
    
    DrawRectangleLinesEx(soundToggleBox, 2, DARKGREEN);
    if (soundEnabled) {
        Rectangle innerBox = { soundToggleBox.x + 4, soundToggleBox.y + 4,
                               soundToggleBox.width - 8, soundToggleBox.height - 8 };
        DrawRectangleRec(innerBox, GREEN);
    }
    DrawText("Sound", soundLabelX, soundLabelY, btnTextSize, DARKGRAY);

    DrawUiButton(&backButton, "Back", btnTextSize);
}

void UnloadSettingsScreen(void) {
    // Nothing to unload yet
}

GameScreen GetSettingsScreen(void) {
    return nextScreen;
}

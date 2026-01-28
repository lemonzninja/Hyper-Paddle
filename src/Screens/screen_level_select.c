/****************************************************************
 *             - The Level Select Screen -
 *  Allows the player to choose between game modes.
 *  Created by Squid on 01/27/2026.
 ****************************************************************/

#include "../../include/UI/UIButton/button.h"
#include "screens.h"


static GameScreen nextScreen;
static GameMode selectedGameMode;

// Buttons
static UIButton singlePlayerButton;
static UIButton twoPlayerButton;
static UIButton backButton;

// Button layout values
static int buttonWidth;
static int buttonHeight;
static int buttonSpacing;
static int titleFontSize;
static int btnTextSize;

void InitLevelSelectScreen(void) {
  titleFontSize = 60;
  btnTextSize = 24;
  buttonHeight = 50;
  buttonWidth = 150;
  buttonSpacing = 70;

  nextScreen = SCREEN_LEVEL_SELECT;
  selectedGameMode = GAME_MODE_SINGLE_PLAYER;

  int centerX = GetScreenWidth() / 2;
  int centerY = GetScreenHeight() / 2;

  // Single Player Button
  int btn1X = centerX - buttonWidth / 2;
  int btn1Y = centerY - 30;
  InitUiButton(&singlePlayerButton, (float)btn1X, (float)btn1Y,
               (float)buttonWidth, (float)buttonHeight, BLUE, DARKBLUE, SKYBLUE,
               WHITE);

  // Two Player Button
  int btn2X = centerX - buttonWidth / 2;
  int btn2Y = btn1Y + buttonSpacing;
  InitUiButton(&twoPlayerButton, (float)btn2X, (float)btn2Y, (float)buttonWidth,
               (float)buttonHeight, GREEN, DARKGREEN, LIME, WHITE);

  // Back Button
  int backX = centerX - buttonWidth / 2;
  int backY = btn2Y + buttonSpacing;
  InitUiButton(&backButton, (float)backX, (float)backY, (float)buttonWidth,
               (float)buttonHeight, GRAY, DARKGRAY, LIGHTGRAY, WHITE);
}

void UpdateLevelSelectScreen(void) {
  UpdateUiButton(&singlePlayerButton);
  UpdateUiButton(&twoPlayerButton);
  UpdateUiButton(&backButton);

  if (IsUiButtonClicked(&singlePlayerButton)) {
    selectedGameMode = GAME_MODE_SINGLE_PLAYER;
    SetGameMode(GAME_MODE_SINGLE_PLAYER);
    nextScreen = SCREEN_MAIN_GAME;
  }

  if (IsUiButtonClicked(&twoPlayerButton)) {
    selectedGameMode = GAME_MODE_TWO_PLAYER;
    SetGameMode(GAME_MODE_TWO_PLAYER);
    nextScreen = SCREEN_MAIN_GAME;
  }

  if (IsUiButtonClicked(&backButton)) {
    nextScreen = SCREEN_MENU;
  }
}

void DrawLevelSelectScreen(void) {
  ClearBackground(BLACK);

  // Title
  const char *title = "Select Mode";
  int titleWidth = MeasureText(title, titleFontSize);
  DrawText(title, (GetScreenWidth() - titleWidth) / 2,
           GetScreenHeight() / 2 - 150, titleFontSize, DARKGRAY);

  // Draw buttons
  DrawUiButton(&singlePlayerButton, "1 Player", btnTextSize);
  DrawUiButton(&twoPlayerButton, "2 Players", btnTextSize);
  DrawUiButton(&backButton, "Back", btnTextSize);
}

void UnloadLevelSelectScreen(void) {
  // Nothing to unload yet
}

GameScreen GetLevelSelectScreen(void) { return nextScreen; }

// Game Mode management - global state
static GameMode currentGameMode = GAME_MODE_SINGLE_PLAYER;

GameMode GetSelectedGameMode(void) { return currentGameMode; }

void SetGameMode(GameMode mode) { currentGameMode = mode; }

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
  buttonHeight = 52;
  buttonWidth = 220;
  buttonSpacing = 74;

  nextScreen = SCREEN_LEVEL_SELECT;
  selectedGameMode = GAME_MODE_SINGLE_PLAYER;

  int centerX = GetScreenWidth() / 2;
  int centerY = GetScreenHeight() / 2;

  // Single Player Button
  int btn1X = centerX - buttonWidth / 2;
  int btn1Y = centerY - 40;
  InitUiButton(&singlePlayerButton, (float)btn1X, (float)btn1Y,
               (float)buttonWidth, (float)buttonHeight,
               (Color){83, 196, 253, 255},
               (Color){112, 214, 255, 255},
               (Color){56, 162, 219, 255},
               (Color){22, 44, 54, 255});

  // Two Player Button
  int btn2X = centerX - buttonWidth / 2;
  int btn2Y = btn1Y + buttonSpacing;
  InitUiButton(&twoPlayerButton, (float)btn2X, (float)btn2Y, (float)buttonWidth,
               (float)buttonHeight,
               (Color){100, 211, 20, 255},
               (Color){134, 235, 44, 255},
               (Color){73, 166, 13, 255},
               (Color){21, 38, 40, 255});

  // Back Button
  int backX = centerX - buttonWidth / 2;
  int backY = btn2Y + buttonSpacing;
  InitUiButton(&backButton, (float)backX, (float)backY, (float)buttonWidth,
               (float)buttonHeight,
               (Color){83, 196, 253, 255},
               (Color){112, 214, 255, 255},
               (Color){56, 162, 219, 255},
               (Color){22, 44, 54, 255});
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
  DrawUiButton(&singlePlayerButton, "1 PLAYER", btnTextSize);
  DrawUiButton(&twoPlayerButton, "2 PLAYERS", btnTextSize);
  DrawUiButton(&backButton, "BACK", btnTextSize);
}

void UnloadLevelSelectScreen(void) {
  // Nothing to unload yet
}

GameScreen GetLevelSelectScreen(void) { return nextScreen; }

// Game Mode management - global state
static GameMode currentGameMode = GAME_MODE_SINGLE_PLAYER;

GameMode GetSelectedGameMode(void) { return currentGameMode; }

void SetGameMode(GameMode mode) { currentGameMode = mode; }

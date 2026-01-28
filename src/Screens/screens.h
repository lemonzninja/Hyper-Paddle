/****************************************************************
 *              - Houses The Screens -
 *  hold the screens for the game
 *  Created by Squid on 10/26/2025.
 ****************************************************************/

#ifndef HYPER_PADDLE_SCREENS_H
#define HYPER_PADDLE_SCREENS_H

#include "raylib.h"

// !Order matters! enum for screens
typedef enum GameScreen {
  SCREEN_LOGO = 0,
  SCREEN_MENU,
  SCREEN_SETTINGS,
  SCREEN_LEVEL_SELECT,
  SCREEN_MAIN_GAME,
  SCREEN_GAME_OVER
} GameScreen;

typedef enum GameMode {
  GAME_MODE_SINGLE_PLAYER = 0,
  GAME_MODE_TWO_PLAYER
} GameMode;

// --ScreenManger functions --
void ScreenManagerInit(void);
void ScreenManagerUpdate(void);
void ScreenManagerDraw(void);
void ScreenManagerUnload(void);

// -- Logo Screen functions --
void InitLogoScreen(void);
void UpdateLogoScreen(void);
void DrawLogoScreen(void);
void UnloadLogoScreen(void);
bool FinishLogoScreen();

// -- Menu Screen functions --
void InitMenuScreen(void);
void UpdateMenuScreen(void);
void DrawMenuScreen(void);
void UnloadMenuScreen(void);
GameScreen GetMainGameScreen(void);

// -- Level Select Screen functions --
void InitLevelSelectScreen(void);
void UpdateLevelSelectScreen(void);
void DrawLevelSelectScreen(void);
void UnloadLevelSelectScreen(void);
GameScreen GetLevelSelectScreen(void);

// -- Game Mode functions --
GameMode GetSelectedGameMode(void);
void SetGameMode(GameMode mode);

// -- Settings Screen functions --
void InitSettingsScreen(void);
void UpdateSettingsScreen(void);
void DrawSettingsScreen(void);
void UnloadSettingsScreen(void);
GameScreen GetSettingsScreen(void);

// -- Game Screen functions --
void InitGameScreen(void);
void UpdateGameScreen(void);
void DrawGameScreen(void);
void UnloadGameScreen(void);
GameScreen GetMenuScreen(void);

#endif // HYPER_PADDLE_SCREENS_H

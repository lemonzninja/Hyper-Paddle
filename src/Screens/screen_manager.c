/****************************************************************
 *               - Screen Manager -
 *   This will handle the switching between screens
 *   Created by Squid on 10/26/2025.
 ****************************************************************/

#include "screens.h"

static GameScreen currentScreen = SCREEN_LOGO;
static GameScreen nextScreen = SCREEN_LOGO;

static void UnloadCurrent(void);
static void NextScreenToInit(void);

void ScreenManagerInit(void) {
  // We set the current screen to the main game screen.
  currentScreen = SCREEN_LOGO;
  nextScreen =
      SCREEN_LOGO; // Initialize the next screen to the main game screen.
  // Now we load the main game screen.
  InitLogoScreen();
}

void ScreenManagerUpdate(void) {
  switch (currentScreen) {
  case SCREEN_LOGO:
    UpdateLogoScreen();
    // Whin the time in the Logo Screen runs out, set "NextScreen" to the Menu
    // Screen.
    if (FinishLogoScreen())
      nextScreen = SCREEN_MENU;
    break;
  case SCREEN_MENU:
    UpdateMenuScreen();
    // Read the menu's desired next screen (set by button callbacks)
    nextScreen = GetMainGameScreen();
    break;
  case SCREEN_SETTINGS:
    UpdateSettingsScreen();
    nextScreen = GetSettingsScreen();
    break;
  case SCREEN_LEVEL_SELECT:
    UpdateLevelSelectScreen();
    nextScreen = GetLevelSelectScreen();
    break;
  case SCREEN_MAIN_GAME:
    UpdateGameScreen();
    nextScreen = GetMenuScreen();
    break;
  default:
    break;
  }

  if (nextScreen != currentScreen) {
    UnloadCurrent();
    currentScreen = nextScreen;
    NextScreenToInit();
  }
}

void ScreenManagerDraw(void) {
  switch (currentScreen) {
  case SCREEN_LOGO:
    DrawLogoScreen();
    break;
  case SCREEN_MENU:
    DrawMenuScreen();
    break;
  case SCREEN_SETTINGS:
    DrawSettingsScreen();
    break;
  case SCREEN_LEVEL_SELECT:
    DrawLevelSelectScreen();
    break;
  case SCREEN_MAIN_GAME:
    DrawGameScreen();
    break;
  default:
    break;
  }
}

void ScreenManagerUnload(void) { UnloadCurrent(); }

void UnloadCurrent(void) {
  switch (currentScreen) {
  case SCREEN_LOGO:
    UnloadLogoScreen();
    break;
  case SCREEN_MENU:
    UnloadMenuScreen();
    break;
  case SCREEN_SETTINGS:
    UnloadSettingsScreen();
    break;
  case SCREEN_LEVEL_SELECT:
    UnloadLevelSelectScreen();
    break;
  case SCREEN_MAIN_GAME:
    UnloadGameScreen();
    break;
  default:
    break;
  }
}

void NextScreenToInit(void) {
  switch (nextScreen) {
  case SCREEN_LOGO:
    InitLogoScreen();
    break;
  case SCREEN_MENU:
    InitMenuScreen();
    break;
  case SCREEN_SETTINGS:
    InitSettingsScreen();
    break;
  case SCREEN_LEVEL_SELECT:
    InitLevelSelectScreen();
    break;
  case SCREEN_MAIN_GAME:
    InitGameScreen();
    break;
  default:
    break;
  }
}

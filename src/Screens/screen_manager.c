/****************************************************************
*               -Screen Manager-
*   This will handle the switching between screens
*   Created by Squid on 10/26/2025.
****************************************************************/

#include "screens.h"

static GameScreen currentScreen = SCREEN_LOGO;
static GameScreen nextScreen = SCREEN_LOGO;

static void UnloadCurrent(void);
static void NextScreenToInit(void);

void ScreenManagerInit(void) {
    // We set the current screen to the logo screen.
    currentScreen = SCREEN_LOGO;
    nextScreen = SCREEN_LOGO; // Initialize the next screen to the logo screen.
    // Now we load the logo screen.
    InitLogoScreen();
}

void ScreenManagerUpdate(void) {
    switch (currentScreen) {
        case SCREEN_LOGO:
            UpdateLogoScreen();
            // Whin the time in the Logo Screen runs out, set "NextScreen" to the Menu Screen.
            if (FinishLogoScreen()) nextScreen = SCREEN_MENU;
            break;
        case SCREEN_MENU:
            UpdateMenuScreen();
            // Read the menu's desired next screen (set by button callbacks)
            nextScreen = FinishMenuScreen();
            break;
        default: break;
    }

    // Transition if screen changed
    if (nextScreen != currentScreen)
    {
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
        default:
            break;
    }
}

void ScreenManagerUnload(void) {
    UnloadCurrent();
}

void UnloadCurrent(void) {
    switch (currentScreen) {
        case SCREEN_LOGO:
            UnloadLogoScreen();
            break;
        case SCREEN_MENU:
           UnloadMenuScreen();
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
        case SCREEN_MENU: InitMenuScreen();
        default:
            break;
    }
}
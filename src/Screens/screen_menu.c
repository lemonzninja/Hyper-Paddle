/****************************************************************
 *             -The Mane Menu Screen-
 *  All the logic for a Mane Menu of are game.
 *  Created by Squid on 10/27/2025.
****************************************************************/

#include "screens.h"
#include "../../include/UI/Buttons/buttons.h"

// Start button values
static GameScreen nextScreen;

// Callback: start the game when the button is clicked
static void OnStart(void* userData)
{
    (void)userData; // unused
    nextScreen = SCREEN_MAIN_GAME;
}

void InitMenuScreen(void)
{
    nextScreen = SCREEN_MENU;
}

void UpdateMenuScreen(void)
{

}

void DrawMenuScreen(void)
{
    // Title
    const char* title = "Hyper Paddle";
    int titleFont = 40;
    int titleWidth = MeasureText(title, titleFont);
    DrawText(title, (GetScreenWidth() - titleWidth)/2, (int)((GetScreenHeight()/2.0f) - 120), titleFont, DARKGRAY);

}

void UnloadMenuScreen(void)
{
    // Nothing to unload yet
}

GameScreen FinishMenuScreen(void)
{
    return nextScreen;
}
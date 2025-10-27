/****************************************************************
 *             -The Mane Menu Screen-
 *  All the logic for a Mane Menu of are game.
 *  Created by Squid on 10/27/2025.
****************************************************************/

#include "screens.h"

static GameScreen nextScreen;

void InitMenuScreen(void)
{
    nextScreen = SCREEN_MENU;
}

void UpdateMenuScreen(void)
{

}

void DrawMenuScreen(void)
{
    DrawText("Menu Screen", GetScreenWidth() / 2, GetScreenHeight() / 2, 10, DARKGRAY);
}

void UnloadMenuScreen(void)
{

}

GameScreen FinishMenuScreen(void){
    return nextScreen;
}
/****************************************************************
*   - The Screen of the Main game -
* Created by Squid on 10/28/2025.
****************************************************************/

#include "screens.h"
#include "../GameManager/Game_Manager.h"

static GameScreen nextScreen;

void InitGameScreen(void) {
    InitMainGame();
}

void UpdateGameScreen(void) {
    UpdateMainGame();
}

void DrawGameScreen(void) {
    ClearBackground(BLACK);
    drawMainGame();

}

void UnloadGameScreen(void) {

}

GameScreen FinishGameScreen(void) {
    return nextScreen;
}
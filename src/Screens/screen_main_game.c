//
// Created by Squid on 10/28/2025.
//

#include "screens.h"
static GameScreen nextScreen;

void InitGameScreen(void) {
}

void UpdateGameScreen(void) {
}

void DrawGameScreen(void) {
    const char *text = "In The game screen!";
    int fontSize = 40;
    int textWidth = MeasureText(text, fontSize);
    DrawText(text,
             (GetScreenWidth() - textWidth) / 2,
             GetScreenHeight() / 2,
             fontSize,
             LIGHTGRAY);
}

void UnloadGameScreen(void) {
    ClearBackground(BLACK);
}

GameScreen FinisGameScreen(void) {

    return nextScreen;
}

/****************************************************************
*              - Hyper Paddle -
*  A Pong clone Made in C using Raylib A simple -
*  and easy-to-use library to enjoy video games programming.
*  Created by Squid on 10/25/2025
****************************************************************/

#include <stdbool.h>
#include <stdio.h>
#include "raylib.h"
#include "Screens/screens.h"

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720
#define Hyp_Paddle_Title "Hyper Paddle"
#define Hyp_Paddle_Version "0.0.9"
char gameTitle[64];
int frames = 0;
bool gameShouldClose = false;

void UpdateDrawFrame(void);   // Update and Draw one frame
void InitGame(void);
void UpdateGame(void);
void DrawGame(void);
void Unload(void);

int main(void)
{
    // Combine the title and version into a single string.
    snprintf(gameTitle, sizeof(gameTitle), "%s %s", Hyp_Paddle_Title, Hyp_Paddle_Version);

    // Init the Game/Items
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, gameTitle);
    InitAudioDevice();
    InitGame();

    frames = 120;

    // Set FPS
    SetTargetFPS(frames);

    // Main game loop
    while (!WindowShouldClose() && !gameShouldClose)   // Detect window close button or ESC key
    {
        UpdateDrawFrame();
    }
    // De-Initialization
    Unload();  // Unload Assets.
    CloseAudioDevice();
    CloseWindow(); // Close the window and OpenGL context
    // End of program.
    return 0;
}

void UpdateDrawFrame(void)
{   // Updating the game
    UpdateGame();
    // Drawing the Game.
    BeginDrawing();
        DrawGame();
    EndDrawing();
}

void InitGame(void)
{
    ScreenManagerInit();
}

void UpdateGame(void)
{
    // Update The Screens with the Screen Manager.
    ScreenManagerUpdate();
}

void DrawGame(void)
{
    // Draw all the screens with the Screen Manager.
    //use draw text to show fps in the top-left corner. with small text.
    DrawText(TextFormat("FPS:  %02i", GetFPS()), 10, 10, 10, DARKGRAY);

    ScreenManagerDraw();
}

void Unload(void) {
    // Unload the Screens items.
    ScreenManagerUnload();
}
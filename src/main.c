#include <strsafe.h>
#include "raylib.h"

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720
#define Hyp_Paddle_Title "Hyper Paddle"
#define Hyp_Paddle_Version "0.0.1"
char gameTitle[64];

int frames = 0;
float deltaTime = 0.0f;

void UpdateDrawFrame(void);   // Update and Draw one frame
void InitGame(void);
void UpdateGame(void);
void DrawGame(void);

int main()
{
    // Combine the title and version into a single string.
    StringCchPrintfA(gameTitle, sizeof(gameTitle), "%s %s", Hyp_Paddle_Title, Hyp_Paddle_Version);

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, gameTitle);

    InitGame();

    frames = 60;
    SetTargetFPS(frames);   // Set our game to run at 60 frames-per-second
    deltaTime = GetFrameTime();

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        UpdateDrawFrame();
    }
    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close the window and OpenGL context
    //--------------------------------------------------------------------------------------
    return 0;
}

void UpdateDrawFrame(void)
{
    UpdateGame();

    BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawGame();
    EndDrawing();
}

void InitGame(void)
{

}

void UpdateGame(void)
{
    //use draw text to show fps in the top-left corner. with small text.
    DrawText(TextFormat("FPS:  %02i", GetFPS()), 10, 10, 10, DARKGRAY);
}

void DrawGame(void)
{

}
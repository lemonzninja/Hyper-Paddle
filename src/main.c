#include <strsafe.h>
#include "raylib.h"
#include "Screens/screens.h"

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720
#define Hyp_Paddle_Title "Hyper Paddle"
#define Hyp_Paddle_Version "0.0.1"
char gameTitle[64];
int frames = 0;

void UpdateDrawFrame(void);   // Update and Draw one frame
void InitGame(void);
void UpdateGame(void);
void DrawGame(void);
void Unload(void);

int main(void)
{
    // Combine the title and version into a single string.
    StringCchPrintfA(gameTitle, sizeof(gameTitle), "%s %s", Hyp_Paddle_Title, Hyp_Paddle_Version);

    // Init the Game/Items
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, gameTitle);
    InitGame();

    // Set FPS.
    frames = 60;
    SetTargetFPS(frames);   // Set our game to run at 60 frames-per-second

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        UpdateDrawFrame();
    }

    // De-Initialization
    Unload();  // Unload Assets.
    CloseWindow(); // Close the window and OpenGL context
    // End of program.
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
    ScreenManagerInit();
}

void UpdateGame(void)
{
    //use draw text to show fps in the top-left corner. with small text.
    DrawText(TextFormat("FPS:  %02i", GetFPS()), 10, 10, 10, DARKGRAY);
    // Update The Screens with the Screen Manager.
    ScreenManagerUpdate();
}

void DrawGame(void)
{
    // Draw all the screens with the Screen Manger.
    ScreenManagerDraw();
}

void Unload(void) {
    // Unload the Screens items.
    ScreenManagerUnload();
}

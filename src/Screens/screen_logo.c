/****************************************************************
*              - The Logo Screen -
*  Created by Squid on 10/26/2025
****************************************************************/

#include <stdbool.h>
#include "screens.h"
#include "raylib.h"

// Variable to store the logo texture
Texture2D logoTexture;

// make a timer for the logo screen
static float logoTimer = 0.0f;
// make a bool for the logo screen
static bool logoDone = false;

void InitLogoScreen(void) {
    // Loading the logo image
    logoTexture = LoadTexture("assets/textures/logo.png");

    logoTimer = 0.0f;
    logoDone = false;
}

void DrawLogoScreen(void) {
    ClearBackground(BLACK);

    // Draw the logo image in the center of the screen
    DrawTexture(logoTexture, GetScreenWidth()/2
    - logoTexture.width/2, GetScreenHeight()/2
    - logoTexture.height/2, WHITE);
}

void UpdateLogoScreen(void) {
    // Update the logo timer
    logoTimer += GetFrameTime();

    // Show the logo screen after 2 seconds and or the mouse is clicked
    if (logoTimer > 2.0f || IsKeyPressed(KEY_ENTER) || IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        // Set the logo screen as done
        logoDone = true;
}

void UnloadLogoScreen(void) {
    UnloadTexture(logoTexture);
}

// when the screen timer is done return true
bool FinishLogoScreen() {
    return logoDone;
}
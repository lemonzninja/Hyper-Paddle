/****************************************************************
 *              - The Manager For key press -
 *  Functions to return the key presses for the game
 *  Created by Squid on 10/29/2025
 ****************************************************************/
#include "Systems/KeyboardManager/keyboardManager.h"

bool IsUpPressed(void) { return IsKeyDown(KEY_W) || IsKeyDown(KEY_UP); }

bool IsDownPressed(void) { return IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN); }

bool IsPlayer2UpPressed(void) { return IsKeyDown(KEY_I);}

bool IsPlayer2DownPressed(void) { return IsKeyDown(KEY_K); }
/****************************************************************
 *              - The Manager For key press -
 *  Functions to return the key presses for the game
 *  Created by Squid on 10/29/2025
 ****************************************************************/
#include "Systems/KeyboardManager/keyboardManager.h"
#include "Screens/screens.h"

bool IsUpPressed(void) {
  if (GetSelectedGameMode() == GAME_MODE_TWO_PLAYER) {
    return IsKeyDown(KEY_W);
  }
  return IsKeyDown(KEY_W) || IsKeyDown(KEY_UP);
}

bool IsDownPressed(void) {
  if (GetSelectedGameMode() == GAME_MODE_TWO_PLAYER) {
    return IsKeyDown(KEY_S);
  }
  return IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN);
}

bool IsPlayer2UpPressed(void) { return IsKeyDown(KEY_UP); }

bool IsPlayer2DownPressed(void) { return IsKeyDown(KEY_DOWN); }

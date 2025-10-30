//
// Created by Squid on 10/29/2025.
//

#include "Systems/KeybordManager/KeybordManager.h"


bool IsUpPressed() {
    return IsKeyDown(KEY_W) || IsKeyDown(KEY_UP);
}

bool IsDownPressed() {
    return IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN);
}
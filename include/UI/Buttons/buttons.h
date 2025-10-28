/****************************************************************
 *              -UI Buttons-
 *  All the buttons for the game
 *  Created by Squid on 10/26/2025.
****************************************************************/

#include "raylib.h"

#ifndef HYPER_PADDLE_BUTTONS_H
#define HYPER_PADDLE_BUTTONS_H

typedef struct UIButton {
    Rectangle rectangle;
    Color color;
}UIButton;

void InitUiButtons(UIButton* uiButton, int x, int y, int width, int height, Color color);
void DrawUiButtons(UIButton* uiButton, char* text, int fontSize);

#endif //HYPER_PADDLE_BUTTONS_H

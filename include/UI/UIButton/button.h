/****************************************************************
 *              -UI UIButton-
 *  All the buttons for the game
 *  Created by Squid on 10/26/2025.
****************************************************************/
#ifndef HYPER_PADDLE_BUTTONS_H
#define HYPER_PADDLE_BUTTONS_H

#include "raylib.h"

// button state management
typedef enum {
    BUTTON_IDLE,
    BUTTON_HOVER,
    BUTTON_CLICKED
} ButtonState;

typedef struct UIButton {
    Rectangle bounds;
    Color NormalColor;
    Color HoverColor;
    Color ClickedColor;
    ButtonState currentState;
    Rectangle rectangle;
    Color textColor;
}UIButton;

void InitUiButton(UIButton* uiButton, float x, float y, float width, float height, Color idleColor, Color hoverColor, Color clickedColor, Color textColor);
void UpdateUiButton(UIButton* uiButton);
void DrawUiButton(const UIButton* uiButton, const char* text, int fontSize);
bool IsUiButtonClicked(const UIButton* uiButton);

#endif //HYPER_PADDLE_BUTTONS_H

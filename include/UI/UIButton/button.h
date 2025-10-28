/****************************************************************
 *              -UI UIButton-
 *  All the buttons for the game
 *  Created by Squid on 10/26/2025.
****************************************************************/

#include "raylib.h"

#ifndef HYPER_PADDLE_BUTTONS_H
#define HYPER_PADDLE_BUTTONS_H

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
    ButtonState state;
    Rectangle rectangle;
    Color color;
    Color textcolor;
}UIButton;

void InitUiButton(UIButton* uiButton, int x, int y,int width,
    int height, Color idleColor,
    Color hoverColor,
    Color clickedColor, Color textColor);
void DrawUiButton(UIButton* uiButton,const char* text, int fontSize);
void UpdateUiButton(UIButton* uiButton);
bool IsUiButtonClicked(UIButton* uiButton);

#endif //HYPER_PADDLE_BUTTONS_H

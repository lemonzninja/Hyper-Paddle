/****************************************************************
 *              -UI UIButton-
 *
 *  Created by Squid on 10/26/2025.
 ****************************************************************/

#include "../../../include/UI/UIButton/button.h"

Vector2 mousePosition = {0.0f,0.0f};

void InitUiButton(UIButton *uiButton, int x, int y, int width, int height,
    const Color idleColor, const Color hoverColor,
    const Color clickedColor, const Color textColor) {
    uiButton->bounds.x = x;
    uiButton->bounds.y = y;
    uiButton->bounds.width = width;
    uiButton->bounds.height = height;
    uiButton->NormalColor = idleColor;
    uiButton->HoverColor = hoverColor;
    uiButton->ClickedColor = clickedColor;
    uiButton->state = BUTTON_IDLE;
    uiButton->textcolor = textColor;
}

void DrawUiButton(UIButton* uiButton, const char* text, int fontSize){
    // Get the center of the button.
    const Rectangle bounds = uiButton->bounds;
    const int btnCenterX = (int)(bounds.x + bounds.width * 0.5f);
    const int btnCenterY = (int)(bounds.y + bounds.height * 0.5f);

    // Text Size
    const int textWidth = MeasureText(text, fontSize);
    const int textHeight = fontSize;

    // Center text position
    const int textx = btnCenterX - (textWidth / 2);
    const int texty = btnCenterY - (textHeight / 2);

    // Draw the button
    Color currentColor = uiButton->NormalColor;
    if (uiButton->state == BUTTON_HOVER) currentColor = uiButton->HoverColor;
    if (uiButton->state == BUTTON_CLICKED) currentColor = uiButton->ClickedColor;

    DrawRectangle(bounds.x, bounds.y, bounds.width, bounds.height, currentColor);
    DrawText(text, textx, texty, fontSize, uiButton->textcolor);
}

void UpdateUiButton(UIButton *uiButton) {
    mousePosition = GetMousePosition();
    
    if (CheckCollisionPointRec(mousePosition, uiButton->bounds)) {
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
            uiButton->state = BUTTON_CLICKED;
        } else {
            uiButton->state = BUTTON_HOVER;
        }
    } else {
        uiButton->state = BUTTON_IDLE;
    }
}

bool IsUiButtonClicked(UIButton *uiButton) {
    // Check if the mouse is on the button and the left mouse button is cliked
    if (CheckCollisionPointRec(GetMousePosition(), uiButton->bounds) &&
        IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        return true;
        }

    return false;
}


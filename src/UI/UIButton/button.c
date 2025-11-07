/****************************************************************
 *              -UI UIButton-
 *
 *  Created by Squid on 10/26/2025.
 ****************************************************************/
#include "../../../include/UI/UIButton/button.h"

Vector2 mousePosition = {0.0f,0.0f};

void InitUiButton(UIButton *uiButton, const float x, const float y, const float width, const float height,
    const Color idleColor, const Color hoverColor,
    const Color clickedColor, const Color textColor) {
    uiButton->bounds.x = x;
    uiButton->bounds.y = y;
    uiButton->bounds.width = width;
    uiButton->bounds.height = height;
    uiButton->NormalColor = idleColor;
    uiButton->HoverColor = hoverColor;
    uiButton->ClickedColor = clickedColor;
    uiButton->currentState = BUTTON_IDLE;
    uiButton->textcolor = textColor;
}

void UpdateUiButton(UIButton *uiButton) {
    if (CheckCollisionPointRec(mousePosition, uiButton->bounds)) {
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
            uiButton->currentState = BUTTON_CLICKED;
        } else {
            uiButton->currentState = BUTTON_HOVER;
        }
    } else {
        uiButton->currentState = BUTTON_IDLE;
        mousePosition = GetMousePosition();
    }
}

void DrawUiButton(const UIButton* uiButton, const char* text, int fontSize){
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
    if (uiButton->currentState == BUTTON_HOVER) currentColor = uiButton->HoverColor;
    if (uiButton->currentState == BUTTON_CLICKED) currentColor = uiButton->ClickedColor;

    DrawRectangle((int)bounds.x, (int)bounds.y, (int)bounds.width, (int)bounds.height, currentColor);
    DrawText(text, textx, texty, fontSize, uiButton->textcolor);
}

bool IsUiButtonClicked(const UIButton *uiButton) {
    // Check if the mouse is on the button and the left mouse button is cliked
    if (CheckCollisionPointRec(GetMousePosition(), uiButton->bounds) &&
        IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        return true;
        }
    return false;
}
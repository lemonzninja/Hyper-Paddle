/****************************************************************
 *              -UI UIButton-
 *
 *  Created by Squid on 10/26/2025.
 ****************************************************************/
#include "../../../include/UI/UIButton/button.h"

static Vector2 mousePosition = {0.0f, 0.0f};

static Color SelectButtonColor(const UIButton *uiButton) {
    if (uiButton->currentState == BUTTON_HOVER) {
        return uiButton->HoverColor;
    }

    if (uiButton->currentState == BUTTON_CLICKED) {
        return uiButton->ClickedColor;
    }

    return uiButton->NormalColor;
}

static Color BrightenColor(const Color color, const float factor) {
    Color adjusted = color;
    adjusted.r = (unsigned char) ((float) adjusted.r + (255.0f - (float) adjusted.r) * factor);
    adjusted.g = (unsigned char) ((float) adjusted.g + (255.0f - (float) adjusted.g) * factor);
    adjusted.b = (unsigned char) ((float) adjusted.b + (255.0f - (float) adjusted.b) * factor);
    return adjusted;
}

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
    uiButton->textColor = textColor;
}

void UpdateUiButton(UIButton *uiButton) {
    mousePosition = GetMousePosition();
    if (CheckCollisionPointRec(mousePosition, uiButton->bounds)) {
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
            uiButton->currentState = BUTTON_CLICKED;
        } else {
            uiButton->currentState = BUTTON_HOVER;
        }
    } else {
        uiButton->currentState = BUTTON_IDLE;
    }
}

void DrawUiButton(const UIButton* uiButton, const char* text, int fontSize){
    const Rectangle bounds = uiButton->bounds;
    const Color baseColor = SelectButtonColor(uiButton);
    const Color borderColor = (Color) {15, 26, 35, 255};
    const Color innerOutlineColor = (Color) {255, 255, 255, 120};
    const Color highlightColor = BrightenColor(baseColor, 0.35f);

    Rectangle fillRect = bounds;
    int textOffsetY = 0;
    if (uiButton->currentState == BUTTON_CLICKED) {
        fillRect.y += 2.0f;
        textOffsetY = 2;
    }

    DrawRectangleRounded(fillRect, 1.0f, 12, borderColor);

    Rectangle innerRect = {
            fillRect.x + 3.0f,
            fillRect.y + 3.0f,
            fillRect.width - 6.0f,
            fillRect.height - 6.0f
    };
    DrawRectangleRounded(innerRect, 1.0f, 12, baseColor);
    DrawRectangleRoundedLinesEx(innerRect, 1.0f, 12, 1.0f, innerOutlineColor);

    Rectangle highlightClip = {
            innerRect.x,
            innerRect.y,
            innerRect.width,
            innerRect.height * 0.45f
    };

    BeginScissorMode((int) highlightClip.x, (int) highlightClip.y,
                     (int) highlightClip.width, (int) highlightClip.height);
    DrawRectangleRounded(innerRect, 1.0f, 12, highlightColor);
    EndScissorMode();

    const int textWidth = MeasureText(text, fontSize);
    const int textX = (int) (fillRect.x + (fillRect.width - (float) textWidth) / 2.0f);
    const int textY = (int) (fillRect.y + (fillRect.height - (float) fontSize) / 2.0f) + textOffsetY;
    DrawText(text, textX, textY, fontSize, uiButton->textColor);
}

bool IsUiButtonClicked(const UIButton *uiButton) {
    // Check if the mouse is on the button and the left mouse button is clicked
    if (CheckCollisionPointRec(GetMousePosition(), uiButton->bounds) &&
        IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        return true;
        }
    return false;
}

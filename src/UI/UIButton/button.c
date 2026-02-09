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

static Color DarkenColor(const Color color, const float factor) {
    Color adjusted = color;
    adjusted.r = (unsigned char) ((float) adjusted.r * (1.0f - factor));
    adjusted.g = (unsigned char) ((float) adjusted.g * (1.0f - factor));
    adjusted.b = (unsigned char) ((float) adjusted.b * (1.0f - factor));
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
    const Color borderColor = (Color) {16, 22, 28, 255};
    const Color outerFillColor = DarkenColor(baseColor, 0.33f);
    const Color highlightColor = BrightenColor(baseColor, 0.22f);
    const Color shadowColor = DarkenColor(baseColor, 0.26f);
    const Color shineLineColor = (Color) {255, 255, 255, 95};

    Rectangle fillRect = bounds;
    int textOffsetY = 0;
    if (uiButton->currentState == BUTTON_CLICKED) {
        fillRect.y += 1.0f;
        textOffsetY = 1;
    }

    DrawRectangleRounded(fillRect, 1.0f, 8, borderColor);

    Rectangle outerRect = {
            fillRect.x + 2.0f,
            fillRect.y + 2.0f,
            fillRect.width - 4.0f,
            fillRect.height - 4.0f
    };
    DrawRectangleRounded(outerRect, 1.0f, 8, outerFillColor);

    Rectangle innerRect = {
            outerRect.x + 2.0f,
            outerRect.y + 2.0f,
            outerRect.width - 4.0f,
            outerRect.height - 4.0f
    };
    DrawRectangleRounded(innerRect, 1.0f, 8, baseColor);
    DrawRectangleRoundedLinesEx(innerRect, 1.0f, 8, 1.0f, shineLineColor);

    Rectangle highlightClip = {innerRect.x, innerRect.y, innerRect.width, innerRect.height * 0.35f};
    Rectangle shadowClip = {
            innerRect.x,
            innerRect.y + innerRect.height * 0.60f,
            innerRect.width,
            innerRect.height * 0.40f
    };

    BeginScissorMode((int) highlightClip.x, (int) highlightClip.y,
                     (int) highlightClip.width, (int) highlightClip.height);
    DrawRectangleRounded(innerRect, 1.0f, 8, highlightColor);
    EndScissorMode();

    BeginScissorMode((int) shadowClip.x, (int) shadowClip.y,
                     (int) shadowClip.width, (int) shadowClip.height);
    DrawRectangleRounded(innerRect, 1.0f, 8, shadowColor);
    EndScissorMode();

    const int textWidth = MeasureText(text, fontSize);
    const int textX = (int) (fillRect.x + (fillRect.width - (float) textWidth) / 2.0f);
    const int textY = (int) (fillRect.y + (fillRect.height - (float) fontSize) / 2.0f) + textOffsetY;
    Color textShadow = DarkenColor(uiButton->textColor, 0.70f);
    textShadow.a = 200;
    DrawText(text, textX + 1, textY + 1, fontSize, textShadow);
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

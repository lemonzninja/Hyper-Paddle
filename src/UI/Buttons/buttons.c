/****************************************************************
 *              -UI Buttons-
 *
 *  Created by Squid on 10/26/2025.
 ****************************************************************/

#include "../../../include/UI/Buttons/buttons.h"

void InitUiButtons(UIButton* uiButton, int x, int y, int width, int height, Color color){
    uiButton->rectangle.x = x;
    uiButton->rectangle.y = y;
    uiButton->rectangle.width = width;
    uiButton->rectangle.height = height;
    uiButton->color = color;

}

void DrawUiButtons(UIButton* uiButton, char* text, int fontSize){
    int textToCenter = MeasureText(text, fontSize);
    int textx = uiButton->rectangle.x + (uiButton->rectangle.width/2) - (textToCenter/2);
    int texty = uiButton->rectangle.y + (uiButton->rectangle.height/2) - (fontSize/2);

    DrawRectangle(uiButton->rectangle.x, uiButton->rectangle.y,
                  uiButton->rectangle.width,
                  uiButton->rectangle.height,
                  uiButton->color);

    DrawText(text, textx, texty, fontSize, BLACK);
}
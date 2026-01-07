/****************************************************************
*              - Compute Center of Rectangle -
*  Created by Squid on 11/02/2025
****************************************************************/

#include "../include/Math/ComputeCenterYofRectangle.h"

float rect_center_y(const Rectangle* rectangle) {
    // Compute the vertical center without modifying the input rectangle
    const float centerY = rectangle->y + (rectangle->height * 0.5f);
    return centerY;
}
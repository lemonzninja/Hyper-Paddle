//
// Created by Squid on 11/2/2025.
//

#include "../include/Math/ComputeCenterYofRectangle.h"

float rect_center_y(const Rectangle* rectangle) {
    return rectangle->y + rectangle->height * 0.5f;
}
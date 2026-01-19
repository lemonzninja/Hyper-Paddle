/****************************************************************
 *              - Math Utilities -
 *  Created by Squid on 01/18/2026
 ****************************************************************/

#include "Math/Utils.h"

float ClampFloat(const float value, const float min, const float max) {
    if (value < min) return min;
    if (value > max) return max;
    return value;
}

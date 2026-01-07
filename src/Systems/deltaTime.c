/****************************************************************
*              - Delta Time System -
*   Spike-resistant delta time with light smoothing.
* - Clamps very large frame times (e.g., when dragging the window or after stalls)
* - Applies an EMA to reduce micro-jitter without adding a noticeable latency
*
* Tune constants below to your preference.
*
*  Created by Squid on 10/29/2025
****************************************************************/


#include "Systems/deltaTime.h"

// Spike-resistant delta time with light smoothing.
// - Clamps very large frame times (e.g., when dragging the window or after stalls)
// - Applies an EMA to reduce micro-jitter without adding a noticeable latency
// Tune constant below to your preference.
float deltaTime(void) {

    // static float delta_Time = 0.0f;
    // delta_Time = GetFrameTime();
    // return delta_Time;

    // Reasonable bounds: allow slo-mo down to 20 FPS equivalent, block huge spikes
    const float MAX_DT = 0.05f;   // 50 ms (cap)
    const float MIN_DT = 0.0f;    // never negative

    // EMA smoothing factor: 0 = no update, 1 = no smoothing. 0.1–0.3 is typical.
    const float SMOOTHING_ALPHA = 0.2f;

    // Start near 60 FPS to avoid the initial burst
    static float smoothed = 1.0f / 60.0f;

    float delta_Time = GetFrameTime();
    if (delta_Time < MIN_DT) delta_Time = MIN_DT;
    if (delta_Time > MAX_DT) delta_Time = MAX_DT;

    // Exponential moving average
    smoothed += (delta_Time - smoothed) * SMOOTHING_ALPHA;
    return smoothed;
}

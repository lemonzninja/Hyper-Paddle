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
// Tune constants below to your preference.
float deltaTime(void) {
    // Reasonable bounds: allow slow-mo down to 20 FPS equivalent, block huge spikes
    const float MAX_DT = 0.05f;   // 50 ms (cap)
    const float MIN_DT = 0.0f;    // never negative

    // EMA smoothing factor: 0 = no update, 1 = no smoothing. 0.1–0.3 is typical.
    const float SMOOTHING_ALPHA = 0.2f;

    // Start near 60 FPS to avoid the initial burst
    static float smoothed = 1.0f / 60.0f;

    float dt = GetFrameTime();
    if (dt < MIN_DT) dt = MIN_DT;
    if (dt > MAX_DT) dt = MAX_DT;

    // Exponential moving average
    smoothed += (dt - smoothed) * SMOOTHING_ALPHA;
    return smoothed;
}

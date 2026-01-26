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
#include "raylib.h"

// Spike-resistant delta time with light smoothing.
// - Clamps very large frame times (e.g., when dragging the window or after stalls)
// - Applies an EMA to reduce micro-jitter without adding a noticeable latency
// Tune constant below to your preference.
static float smoothedDeltaTime = 1.0f / 120.0f;
static float currentDeltaTime = 1.0f / 120.0f;

void UpdateDeltaTime(void) {
    // Reasonable bounds: allow slo-mo down to 20 FPS equivalent, block huge spikes
    const float MAX_DT = 0.05f;   // 50 ms (cap)
    const float MIN_DT = 0.0f;    // never negative

    // EMA smoothing factor: Increased to 0.35 for faster response and less input lag
    const float SMOOTHING_ALPHA = 0.35f;

    currentDeltaTime = GetFrameTime();
    if (currentDeltaTime < MIN_DT) currentDeltaTime = MIN_DT;
    if (currentDeltaTime > MAX_DT) currentDeltaTime = MAX_DT;

    // Exponential moving average
    smoothedDeltaTime += (currentDeltaTime - smoothedDeltaTime) * SMOOTHING_ALPHA;
}

float rawDeltaTime(void) {
    return currentDeltaTime;
}


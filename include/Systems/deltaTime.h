//
// Created by Squid on 10/29/2025.
//

#ifndef HYPER_PADDLE_DELTATIME_H
#define HYPER_PADDLE_DELTATIME_H

#include "raylib.h"

// Spike-resistant delta time with light smoothing.
// - Clamps very large frame times (e.g., when dragging the window or after stalls)
// - Applies an EMA to reduce micro-jitter without adding noticeable latency
// Tune constants below to your preference.
float deltaTime(void);

#endif // HYPER_PADDLE_DELTATIME_H

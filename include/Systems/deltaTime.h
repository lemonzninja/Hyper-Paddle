/****************************************************************
*              - Delta Time System -
*   Spike-resistant delta time with light smoothing.
* - Clamps very large frame times (e.g., when dragging the window or after stalls)
* - Applies an EMA to reduce micro-jitter without adding a noticeable latency
*
*  Created by Squid on 10/29/2025
****************************************************************/

#ifndef HYPER_PADDLE_DELTATIME_H
#define HYPER_PADDLE_DELTATIME_H

void UpdateDeltaTime(void);
float rawDeltaTime(void);

#endif // HYPER_PADDLE_DELTATIME_H

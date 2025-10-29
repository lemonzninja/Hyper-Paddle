//
// Created by Squid on 10/29/2025.
//

#ifndef HYPER_PADDLE_DELTATIME_H
#define HYPER_PADDLE_DELTATIME_H



static float deltaTime(void) {
    static float delta_Time = 0.0f;
    delta_Time = GetFrameTime();
    return delta_Time;
}

#endif //HYPER_PADDLE_DELTATIME_H
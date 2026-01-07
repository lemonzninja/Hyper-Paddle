/****************************************************************
*              - Ball Game Object -
*  Created by Squid on 10/30/2025
****************************************************************/

#ifndef HYPER_PADDLE_BALL_H
#define HYPER_PADDLE_BALL_H
#include "raylib.h"

typedef struct Ball {
    Rectangle Shape;
    Color BallColor;
    Vector2 Velocity;
    bool isLeftSide;
    bool isRightSide;
    Sound bounceSound;
}Ball;

void InitBall(Ball *ball, float x, float y, float width, float height, float velocity, Color color);
void ResetBall(Ball* ball, float x, float y, float velocity);
void UpdateBall(Ball* ball);
void DrawBall(const Ball* ball);
void HandleVerticalBounds(Ball* ball);
void ballDetectGoal(Ball* ball);
void UnloadBall(const Ball* ball);

#endif //HYPER_PADDLE_BALL_H
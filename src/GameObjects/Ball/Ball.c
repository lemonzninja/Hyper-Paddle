/****************************************************************
 *              - Ball Game Object -
 *  Created by Squid on 10/30/2025
 ****************************************************************/

#include "GameObjects/Ball/Ball.h"
#include "Systems/deltaTime.h"
#include "config.h"
#include <math.h>

// Ball physics constants
static const float BALL_VERTICAL_RANGE_FACTOR = 0.65f;
static const float BALL_MIN_VERTICAL_FACTOR = 0.2f;
static const float BALL_DEFAULT_VERTICAL_FACTOR = 0.25f;

static float RandomizeBallVerticalSpeed(const float velocity) {
  const float speed = fabsf(velocity);
  const float range = speed * BALL_VERTICAL_RANGE_FACTOR;
  // Use multiplication instead of division for better performance
  const float randomScale = (float)GetRandomValue(0, 1000) * 0.001f;
  float vertical = (randomScale * 2.0f - 1.0f) * range;
  if (fabsf(vertical) < speed * BALL_MIN_VERTICAL_FACTOR) {
    vertical = (vertical < 0.0f ? -1.0f : 1.0f) * speed * BALL_DEFAULT_VERTICAL_FACTOR;
  }
  return vertical;
}

void InitBall(Ball *ball, const float x, const float y, const float width, const float height, const float velocity, const Color color) {
  ball->Shape.width = width;
  ball->Shape.height = height;
  ball->BallColor = color;

  ball->timeAccumulator = 0.0f;

  ResetBall(ball, x, y, velocity, 0.0f);

  ball->wallCollisionSound = LoadSound("assets/soundFX/ballsound2.wav");
  ball->paddleCollisionSound = LoadSound("assets/soundFX/ballSound.wav");

  // Validate that sound loaded successfully (check if the stream is valid)
  if (ball->wallCollisionSound.frameCount == 0) {
    TraceLog(LOG_WARNING, "BALL: Failed to load bounce sound");
  }
  if (ball->paddleCollisionSound.frameCount == 0) {
    TraceLog(LOG_WARNING, "BALL: Failed to load paddle sound");
  }
}

void ResetBall(Ball *ball, const float x, const float y, const float velocity, const float directionX) {
  float direction = directionX;
  if (direction == 0.0f) {
    direction = GetRandomValue(0, 1) == 0 ? -1.0f : 1.0f;
  } else {
    direction = (directionX > 0.0f) ? 1.0f : -1.0f;
  }

  ball->Shape.x = x;
  ball->Shape.y = y;
  ball->PreviousPosition = (Vector2){x, y};
  ball->RenderPosition = (Vector2){x, y};
  ball->timeAccumulator = 0.0f;
  ball->Velocity.x = direction * fabsf(velocity);
  ball->Velocity.y = RandomizeBallVerticalSpeed(velocity);
}

void UnloadBall(const Ball *ball) {
  UnloadSound(ball->wallCollisionSound);
  UnloadSound(ball->paddleCollisionSound);
}

void UpdateBall(Ball *ball) {
  ball->timeAccumulator += rawDeltaTime();

  if (ball->timeAccumulator > MAX_ACCUMULATOR) {
    ball->timeAccumulator = MAX_ACCUMULATOR;
  }

  while (ball->timeAccumulator >= FIXED_TIMESTEP) {
    ball->PreviousPosition = (Vector2){ball->Shape.x, ball->Shape.y};
    ball->Shape.x += ball->Velocity.x * FIXED_TIMESTEP;
    ball->Shape.y += ball->Velocity.y * FIXED_TIMESTEP;
    ball->timeAccumulator -= FIXED_TIMESTEP;
  }

  if (ball->timeAccumulator > 0.0f) {
    const float alpha = ball->timeAccumulator / FIXED_TIMESTEP;
    ball->RenderPosition.x = ball->PreviousPosition.x +
                             (ball->Shape.x - ball->PreviousPosition.x) * alpha;
    ball->RenderPosition.y = ball->PreviousPosition.y +
                             (ball->Shape.y - ball->PreviousPosition.y) * alpha;
  } else {
    ball->RenderPosition.x = ball->Shape.x;
    ball->RenderPosition.y = ball->Shape.y;
  }
}

void DrawBall(const Ball *ball) {
  const Rectangle renderShape = {ball->RenderPosition.x, ball->RenderPosition.y,
                                 ball->Shape.width, ball->Shape.height};
  DrawRectangleRec(renderShape, ball->BallColor);
}

void ResetBallInterpolation(Ball *ball) {
  ball->PreviousPosition = (Vector2){ball->Shape.x, ball->Shape.y};
  ball->RenderPosition = ball->PreviousPosition;
  ball->timeAccumulator = 0.0f;
}

void HandleVerticalBounds(Ball *ball) {
  if (ball->Shape.y <= 0.0f) {
    ball->Shape.y = 0.0f;
    ball->Velocity.y = -ball->Velocity.y;
    ResetBallInterpolation(ball);
    PlaySound(ball->wallCollisionSound);
  }

  const float ballBottomSide = ball->Shape.y + ball->Shape.height;

  if (ballBottomSide >= SCREEN_HEIGHT_F) {
    ball->Shape.y = SCREEN_HEIGHT_F - ball->Shape.height;
    ball->Velocity.y = -ball->Velocity.y;
    ResetBallInterpolation(ball);
    PlaySound(ball->wallCollisionSound);
  }
}

BallGoal DetectBallGoal(const Ball *ball) {
  // if the ball hits the left edge have aiScore go up 1.
  if (ball->Shape.x <= 0.0f) {
    return BALL_GOAL_LEFT;
  }

  // if the ball hits the right edge have playerScore go up 1.
  if (ball->Shape.x >= SCREEN_WIDTH_F - ball->Shape.width) {
    return BALL_GOAL_RIGHT;
  }

  return BALL_GOAL_NONE;
}

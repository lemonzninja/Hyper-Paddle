/****************************************************************
 *              - Paddle Game Object -
 *  Created by Squid on 10/28/2025.
 ****************************************************************/

#include "GameObjects/Paddle/Paddle.h"
#include "GameObjects/Ball/Ball.h"
#include "Math/Utils.h"
#include "Systems/KeyboardManager/keyboardManager.h"
#include "Systems/deltaTime.h"
#include "config.h"
#include <stddef.h>
#include <tgmath.h>

// AI behavior constants
static const float AI_ERROR_SPEED_FACTOR = 0.05f;
static const float AI_ERROR_BASE = 16.0f;
static const float AI_REACTION_DELAY = 0.12f;

void InitPaddle(Paddle *paddle, const float x, const float y, const float width,
                const float height, const Color color) {
  paddle->Shape.x = x;
  paddle->Shape.y = y;
  paddle->Shape.width = width;
  paddle->Shape.height = height;
  paddle->PaddleColor = color;
  paddle->targetY = y;
  paddle->PreviousPosition = (Vector2){x, y};
  paddle->RenderPosition = (Vector2){x, y};
  paddle->timeAccumulator = 0.0f;
}

typedef void (*PaddlePhysicsStrategy)(Paddle *paddle, float fixedStep,
                                      float speed, void *context);

// Helper to interpolate render position
static void ApplyPaddleInterpolation(Paddle *paddle, float alpha) {
  paddle->RenderPosition.x =
      paddle->PreviousPosition.x +
      (paddle->Shape.x - paddle->PreviousPosition.x) * alpha;
  paddle->RenderPosition.y =
      paddle->PreviousPosition.y +
      (paddle->Shape.y - paddle->PreviousPosition.y) * alpha;
}

// Core physics update loop
static void UpdatePaddlePhysics(Paddle *paddle, float speed,
                                PaddlePhysicsStrategy strategy, void *context) {
  paddle->timeAccumulator += rawDeltaTime();

  if (paddle->timeAccumulator > MAX_ACCUMULATOR) {
    paddle->timeAccumulator = MAX_ACCUMULATOR;
  }

  while (paddle->timeAccumulator >= FIXED_TIMESTEP) {
    paddle->PreviousPosition = (Vector2){paddle->Shape.x, paddle->Shape.y};

    strategy(paddle, FIXED_TIMESTEP, speed, context);

    // Keep paddle inside screen bounds (safety check)
    const float maxY = SCREEN_HEIGHT_F - paddle->Shape.height;

    if (paddle->Shape.y <= 0.0f) {
      paddle->Shape.y = 0.0f;
    }
    if (paddle->Shape.y > maxY) {
      paddle->Shape.y = maxY;
    }

    paddle->timeAccumulator -= FIXED_TIMESTEP;
  }

  if (paddle->timeAccumulator > 0.0f) {
    const float alpha = paddle->timeAccumulator / FIXED_TIMESTEP;
    ApplyPaddleInterpolation(paddle, alpha);
  } else {
    paddle->RenderPosition.x = paddle->Shape.x;
    paddle->RenderPosition.y = paddle->Shape.y;
  }
}

static void PlayerUpdateStrategy(Paddle *paddle, float fixedStep, float speed,
                                 void *context) {
  // Move up
  if (IsUpPressed()) {
    paddle->Shape.y -= speed * fixedStep;
  }
  // move Down
  if (IsDownPressed()) {
    paddle->Shape.y += speed * fixedStep;
  }
}

void UpdatePlayerPaddle(Paddle *paddle, const float Speed) {
  UpdatePaddlePhysics(paddle, Speed, PlayerUpdateStrategy, NULL);
}

static void Player2UpdateStrategy(Paddle *paddle, float fixedStep, float speed,
                                  void *context) {
  // Move up
  if (IsPlayer2UpPressed()) {
    paddle->Shape.y -= speed * fixedStep;
  }
  // move Down
  if (IsPlayer2DownPressed()) {
    paddle->Shape.y += speed * fixedStep;
  }
}

void UpdatePlayer2Paddle(Paddle *paddle, const float speed) {
  UpdatePaddlePhysics(paddle, speed, Player2UpdateStrategy, NULL);
}

// Decide the AI vertical step based on offset and dead zone
float AiVerticalStep(const float offset_y, const float speed, const float dt,
                     const float dead_zone) {
  if (fabsf(offset_y) <= dead_zone)
    return 0.0f;
  // move up or down by speed * dt depending on the sign of offset
  return (offset_y > 0.0f ? 1.0f : -1.0f) * speed * dt;
}

typedef struct {
  const Ball *ball;
  float *reactionTimer;
} AIContext;

static void AIUpdateStrategy(Paddle *paddle, float fixedStep, float speed,
                             void *context) {
  AIContext *aiData = (AIContext *)context;
  const Ball *ball = aiData->ball;
  float *reactionTimer = aiData->reactionTimer;

  const float maxY = SCREEN_HEIGHT_F - paddle->Shape.height;
  const bool ballMovingRight = ball->Velocity.x > 0.0f;

  *reactionTimer -= fixedStep;
  if (ballMovingRight) {
    if (*reactionTimer <= 0.0f) {
      const float speedX = fabsf(ball->Velocity.x);
      const float distanceX =
          paddle->Shape.x - (ball->Shape.x + ball->Shape.width);
      float prediction = ball->Shape.y;

      if (distanceX > 0.0f && speedX > 0.01f) {
        const float time = distanceX / speedX;
        prediction = ball->Shape.y + ball->Velocity.y * time;

        // Limit iterations to prevent performance issues with very high speeds
        int iterations = 0;
        const int MAX_BOUNCE_ITERATIONS = 10;
        while ((prediction < 0.0f || prediction > maxY) &&
               iterations < MAX_BOUNCE_ITERATIONS) {
          if (prediction < 0.0f) {
            prediction = -prediction;
          } else if (prediction > maxY) {
            prediction = 2.0f * maxY - prediction;
          }
          iterations++;
        }

        // Clamp to valid range if we hit iteration limit
        if (iterations >= MAX_BOUNCE_ITERATIONS) {
          prediction = ClampFloat(prediction, 0.0f, maxY);
        }
      }

      const float errorRange = AI_ERROR_BASE + (speedX * AI_ERROR_SPEED_FACTOR);
      const float error =
          ((float)GetRandomValue(-(int)errorRange, (int)errorRange));
      paddle->targetY = prediction + error;
      *reactionTimer = AI_REACTION_DELAY;
    }
  } else {
    paddle->targetY = maxY * 0.5f;
    *reactionTimer = 0.0f;
  }

  paddle->targetY = ClampFloat(paddle->targetY, 0.0f, maxY);

  const float delta = paddle->targetY - paddle->Shape.y;
  const float maxStep = speed * fixedStep;
  if (fabsf(delta) <= maxStep) {
    paddle->Shape.y = paddle->targetY;
  } else {
    paddle->Shape.y += (delta > 0.0f ? 1.0f : -1.0f) * maxStep;
  }
}

void UpdateAIPaddle(Paddle *paddle, const float Speed, const Ball *ball) {
  static float reactionTimer = 0.0f;
  AIContext context = {ball, &reactionTimer};
  UpdatePaddlePhysics(paddle, Speed, AIUpdateStrategy, &context);
}

void DrawPaddle(const Paddle *paddle) {
  const Rectangle renderShape = {paddle->RenderPosition.x,
                                 paddle->RenderPosition.y, paddle->Shape.width,
                                 paddle->Shape.height};
  DrawRectangleRec(renderShape, paddle->PaddleColor);
}

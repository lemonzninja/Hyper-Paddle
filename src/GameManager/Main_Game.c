/****************************************************************
 *              - The Main game -
 *   All the logic of the Main game goes here.
 *  Created by Squid on 10/29/2025
 ****************************************************************/
#include "Game_Manager.h"
#include "Math/Utils.h"
#include "config.h"
#include <math.h>

static GameScreen nextScreen;

// Game configuration constants
static const float BALL_START_SPEED = 450.0f;
static const float BALL_MAX_SPEED = 900.0f;
static const float BALL_SPEED_INCREMENT = 35.0f;
static const float BALL_MAX_VERTICAL_SPEED = 520.0f;
static const float BALL_VERTICAL_SPIN = 0.85f;
static const float BALL_RADIUS = 10.0f;
static const float PLAYER_PADDLE_SPEED = 420.0f;
static const float AI_PADDLE_SPEED = 420.0f;
static const float SCORE_SIZE = 30.0f;
static const int WIN_SCORE = 5;

// Score display
static Counter playerScoreText;
static Counter aiScoreText;

// Ball
static Ball ball;
static float ballResetX;
static float ballResetY;

// Paddles
static Paddle playerPaddle;
static Paddle aiPaddle;

typedef enum { WINNER_NONE, WINNER_PLAYER, WINNER_AI } Winner;

static bool gameOver = false;
static Winner winner = WINNER_NONE;
static bool gamePaused = false;

static UIButton restartButton;
static UIButton menuButton;

void InitMainGame(void) {
  nextScreen = SCREEN_MAIN_GAME;

  // Calculate ball reset position
  ballResetX = SCREEN_WIDTH_F / 2.0f - BALL_RADIUS;
  ballResetY = 200.0f;

  // Initialize ball (loads sound resource)
  InitBall(&ball, ballResetX, ballResetY, BALL_RADIUS * 2, BALL_RADIUS * 2,
           BALL_START_SPEED, WHITE);

  // Initialize UI buttons (one-time setup)
  InitUiButton(&restartButton, SCREEN_WIDTH_F / 2.0f - 150.0f,
               SCREEN_HEIGHT_F / 2.0f, 100, 50, LIGHTGRAY, WHITE, GRAY, BLACK);
  InitUiButton(&menuButton, SCREEN_WIDTH_F / 2.0f + 50.0f,
               SCREEN_HEIGHT_F / 2.0f, 100, 50, LIGHTGRAY, WHITE, GRAY, BLACK);

  // Reset game state
  ResetMainGame();
}

void ResetMainGame(void) {
  // Reset scores
  InitScore(&playerScoreText, 0, SCREEN_WIDTH_F / 2.0f - 70.0f, 30.0f, WHITE,
            SCORE_SIZE);
  InitScore(&aiScoreText, 0, SCREEN_WIDTH_F / 2.0f + 50.0f, 30.0f, WHITE,
            SCORE_SIZE);

  // Reset paddles to starting positions
  InitPaddle(&playerPaddle, 45, 299, 20, 80, WHITE);
  InitPaddle(&aiPaddle, 1200, 299, 20, 80, WHITE);

  // Reset Ball
  ResetBall(&ball, ballResetX, ballResetY, BALL_START_SPEED, 0.0f);

  // Reset game state
  gameOver = false;
  winner = WINNER_NONE;
  gamePaused = false;
}

void UnloadMainGame(void) { UnloadBall(&ball); }

static void ResetBallAfterScore(Ball *ball, const bool launchTowardsLeft) {
  const float direction = launchTowardsLeft ? -1.0f : 1.0f;
  ResetBall(ball, ballResetX, ballResetY, BALL_START_SPEED, direction);
}

static void GameOverDisplay(void) {
  UpdateUiButton(&restartButton);
  UpdateUiButton(&menuButton);

  if (IsUiButtonClicked(&restartButton)) {
    ResetMainGame();
  }

  if (IsUiButtonClicked(&menuButton)) {
    nextScreen = SCREEN_MENU;
  }
}

static void PauseMenuDisplay(void) {
  UpdateUiButton(&restartButton);
  UpdateUiButton(&menuButton);

  if (IsUiButtonClicked(&restartButton)) {
    ResetMainGame();
  }

  if (IsUiButtonClicked(&menuButton)) {
    nextScreen = SCREEN_MENU;
  }
}

static void HandleBallPaddleCollision(Ball *ball, const Paddle *paddle,
                                      const bool isRightPaddle) {
  if (CheckCollisionRecs(ball->Shape, paddle->Shape)) {
    // Safety check: prevent division by zero if paddle height is invalid
    if (paddle->Shape.height < 1.0f) {
      return;
    }

    if (isRightPaddle) {
      ball->Shape.x = paddle->Shape.x - ball->Shape.width;
    } else {
      ball->Shape.x = paddle->Shape.x + paddle->Shape.width;
    }
    PlaySound(ball->paddleCollisionSound);

    const float paddleCenter = paddle->Shape.y + paddle->Shape.height * 0.5f;
    const float ballCenter = ball->Shape.y + ball->Shape.height * 0.5f;
    const float relative =
        (ballCenter - paddleCenter) / (paddle->Shape.height * 0.5f);
    const float speedX =
        fminf(BALL_MAX_SPEED, fabsf(ball->Velocity.x) + BALL_SPEED_INCREMENT);
    const float newSign = isRightPaddle ? -1.0f : 1.0f;

    ball->Velocity.x = newSign * speedX;
    ball->Velocity.y =
        ClampFloat(relative * BALL_MAX_VERTICAL_SPEED, -BALL_MAX_VERTICAL_SPEED,
                   BALL_MAX_VERTICAL_SPEED) *
        BALL_VERTICAL_SPIN;
    ResetBallInterpolation(ball);
  }
}

static void HandleScore(int goal, Counter *scoreText, Ball *ball,
                        bool resetDirection, bool *gameOver, Winner *winner,
                        Winner winnerValue) {
  if (goal == (resetDirection ? BALL_GOAL_RIGHT : BALL_GOAL_LEFT)) {
    scoreText->score += 1;
    ResetBallAfterScore(ball, resetDirection);
    if (scoreText->score >= WIN_SCORE) {
      *gameOver = true;
      *winner = winnerValue;
    }
  }
}

void UpdateMainGame(void) {
  if (!gameOver && IsKeyPressed(KEY_P)) {
    gamePaused = !gamePaused;
  }

  // If game over, pause gameplay and wait for user input
  if (gameOver) {
    GameOverDisplay();
    return;
  }

  if (gamePaused) {
    PauseMenuDisplay();
    return;
  }

  // Move Paddles
  UpdatePlayerPaddle(&playerPaddle, PLAYER_PADDLE_SPEED);
  UpdateAIPaddle(&aiPaddle, AI_PADDLE_SPEED, &ball);
  // Move Ball
  UpdateBall(&ball);

  // The Ball Paddle Collisions
  HandleBallPaddleCollision(&ball, &playerPaddle,
                            false);                  // The player collision.
  HandleBallPaddleCollision(&ball, &aiPaddle, true); // The AI collision.

  HandleVerticalBounds(&ball);
  const BallGoal goal = DetectBallGoal(&ball);

  HandleScore(goal, &aiScoreText, &ball, false, &gameOver, &winner, WINNER_AI);
  HandleScore(goal, &playerScoreText, &ball, true, &gameOver, &winner,
              WINNER_PLAYER);
}

void drawMainGame(void) {
  ClearBackground(BLACK);

  DrawScore(&playerScoreText);
  DrawScore(&aiScoreText);

  // Draw a dotted line down the middle of the screen in between the players
  // like pong.
  const float centerX = SCREEN_WIDTH_F / 2.0f;
  const float dashHeight = 15.0f;
  const float dashGap = 10.0f;
  for (float y = 0; y < SCREEN_HEIGHT_F; y += dashGap + dashHeight) {
    DrawRectangle((int)(centerX - 2.0f), (int)y, 4, (int)dashHeight, WHITE);
  }

  DrawPaddle(&playerPaddle);
  DrawPaddle(&aiPaddle);

  DrawBall(&ball);

  // Draw overlay if the game is over.
  if (gameOver) {
    const Color menuBackgroundColor = DARKBLUE;
    const Rectangle menuBackground = {SCREEN_WIDTH_F / 2.0f - 200.0f,
                                      SCREEN_HEIGHT_F / 2.0f - 50.0f, 400.0f,
                                      150.0f};

    DrawRectangle((int)menuBackground.x, (int)menuBackground.y,
                  (int)menuBackground.width, (int)menuBackground.height,
                  menuBackgroundColor);

    // Draw "GAME OVER" text
    const char *gameOverText = "GAME OVER";
    const int gameOverFontSize = 40;
    int textWidth = MeasureText(gameOverText, gameOverFontSize);

    DrawText(gameOverText,
             menuBackground.x + (menuBackground.width - (float)textWidth) / 2,
             (int)menuBackground.y - 20, gameOverFontSize, WHITE);

    // Draw winner announcement
    const char *winnerText =
        winner == WINNER_PLAYER ? "Player Wins!" : "AI Wins!";
    const int winnerFontSize = 30;
    textWidth = MeasureText(winnerText, winnerFontSize);
    DrawText(winnerText,
             menuBackground.x + (menuBackground.width - (float)textWidth) / 2,
             (int)menuBackground.y - 60, winnerFontSize, WHITE);

    DrawUiButton(&restartButton, "Restart", 20);
    DrawUiButton(&menuButton, "Exit", 20);
  } else if (gamePaused) {
    const Color menuBackgroundColor = DARKBLUE;
    const Rectangle menuBackground = {SCREEN_WIDTH_F / 2.0f - 200.0f,
                                      SCREEN_HEIGHT_F / 2.0f - 50.0f, 400.0f,
                                      150.0f};

    DrawRectangle((int)menuBackground.x, (int)menuBackground.y,
                  (int)menuBackground.width, (int)menuBackground.height,
                  menuBackgroundColor);

    const char *pausedText = "PAUSED";
    const int pausedFontSize = 40;
    int textWidth = MeasureText(pausedText, pausedFontSize);

    DrawText(pausedText,
             menuBackground.x + (menuBackground.width - (float)textWidth) / 2,
             (int)menuBackground.y - 20, pausedFontSize, WHITE);

    DrawUiButton(&restartButton, "Restart", 20);
    DrawUiButton(&menuButton, "Menu", 20);
  }
}

GameScreen GetMenuScreen(void) { return nextScreen; }
/****************************************************************
*              - The Manager of the game -
*  Created by Squid on 10/29/2025
****************************************************************/

#ifndef HYPER_PADDLE_GAME_MANAGER_H
#define HYPER_PADDLE_GAME_MANAGER_H

#include "../Screens/screens.h"
#include <stdio.h>
#include "raylib.h"
#include "GameObjects/Paddle/Paddle.h"
#include "GameObjects/Ball/Ball.h"
#include "Systems/ScoreManager/ScoreManager.h"
#include "UI/UIButton/button.h"

void InitMainGame();
void UpdateMainGame();
void drawMainGame();
GameScreen GetMainGameScreen();

#endif //HYPER_PADDLE_GAME_MANAGER_H
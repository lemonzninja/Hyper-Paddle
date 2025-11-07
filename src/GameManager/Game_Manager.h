/****************************************************************
*              - The Manager of the game -
*  Created by Squid on 10/29/2025
****************************************************************/

#ifndef HYPER_PADDLE_GAME_MANAGER_H
#define HYPER_PADDLE_GAME_MANAGER_H

#include "raylib.h"
#include "GameObjects/Paddle/Paddle.h"
#include "GameObjects/Ball/Ball.h"
#include "Systems/ScoreManager/ScoreManager.h"

void InitMainGame();
void UpdateMainGame();
void drawMainGame();


#endif //HYPER_PADDLE_GAME_MANAGER_H
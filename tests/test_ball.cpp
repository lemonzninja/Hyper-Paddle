#include <gtest/gtest.h>
extern "C" {
#include "GameObjects/Ball/Ball.h"
}
#include "Systems/deltaTime.h"

// Mock deltaTime function
static float mock_deltaTime = 1.0f;
float deltaTime() {
    return mock_deltaTime;
}

TEST(BallTest, UpdateBall_PositiveVelocity_IncreasesX) {
    Ball ball;
    InitBall(&ball, 0.0f, 0.0f, 10.0f, 10.0f, 5.0f, WHITE);

    float initialX = ball.Shape.x;
    UpdateBall(&ball);

    ASSERT_GT(ball.Shape.x, initialX);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

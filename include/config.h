/****************************************************************
 *              - Game Configuration Constants -
 *  Shared constants used across the game.
 ****************************************************************/

#ifndef CONFIG_H
#define CONFIG_H

// Physics update rate: 120 Hz fixed timestep
static const float FIXED_TIMESTEP = 1.0f / 120.0f;

// Maximum time accumulator to prevent spiral of death
static const float MAX_ACCUMULATOR = 0.1f;

#endif // CONFIG_H

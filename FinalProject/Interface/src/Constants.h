#pragma once
#include "Vec2.h"

//Screen dimension constants
const int PIXELS_PER_METER = 30; // The width of a game grid tile

const int GAME_GRID_WIDTH = 56; // How many tiles wide the game grid is. Should be an even number
const int GAME_GRID_HEIGHT = 32; // How many tiles tall the game grid is. 

const int UI_WIDTH = GAME_GRID_WIDTH; // The width of the UI section to the right of the play area in meters
const int UI_HEIGHT = GAME_GRID_HEIGHT; // The height of the UI Section is the height of the play area

const int SCREEN_WIDTH_PIXELS = PIXELS_PER_METER * GAME_GRID_WIDTH; // The total number of pixels wide the window is
const int SCREEN_HEIGHT_PIXELS = PIXELS_PER_METER * GAME_GRID_HEIGHT; // The total number of pixels tall the window is

// Tick limitations
const float TICK_MIN = 0.05f;
const float TICK_MAX = 0.2f;

const int SHORT_GUNNER_TYPE = 0;
const int SNIPER_TYPE = 1;

const float SHORT_GUNNER_SIZE = 1.0f;
const float SNIPER_SIZE = 1.0f;
const float BULLET_SIZE = 0.3f;

const float COVER_WIDTH = 3.5f;
const float COVER_HEIGHT = 0.2f;

const float ENEMY_SPEED = 3.0f;
const float BULLET_SPEED = 8.0f;
const float PLAYER_SPEED = 0.3f;

const float GUN_LENGTH = 0.8f;
const float GUN_WIDTH = 0.1f;

const float MAX_SIGHT = 20.0f;

const float SHOOTPRIORITY = 3.0f;
const float MOVEPRIORITY = 2.0f;
const float WAITPRIORITY = 1.0f;



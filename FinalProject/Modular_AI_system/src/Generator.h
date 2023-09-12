#pragma once

#include "Game.h"
#include "Cover.h"

class Game;

// Define a ConcreteGenerator class that generates potential positions to shoot enemies
class Generator
{

public:
  // takes in a game object and return all possible cover positions
  std::vector<std::pair<Vec2, char>> generatePositions(Game& game);

};



#pragma once

#include "FloatFunctor.h"
#include "Vec2.h"
#include "Constants.h"
#include <float.h>

// define a Consideration subclass which considers the covers that are in between enemy and players
class CoverToPlayerConsideration : public FloatFunctor
{
  public:
    // takes in player's position and enemy's position
    CoverToPlayerConsideration(Vec2 player_pos, Vec2 enemy_pos) : player_Pos(player_pos), enemy_Pos(enemy_pos) {};

    // evaluate the cover
    float evaluate(const std::pair<Vec2, char> cover);

  private:
    Vec2 player_Pos;
    Vec2 enemy_Pos;
};
#pragma once

#include "FloatFunctor.h"
#include "Vec2.h"

// define a Consideration subclass which considers the side that the cover can cover the enemy
class CoverAngleConsideration : public FloatFunctor
{
public:
  // takes in player's position
  CoverAngleConsideration(Vec2 pos);

  // evaluate the cover
  float evaluate(const std::pair<Vec2, char> cover);

private:
  Vec2 player_Pos;
};
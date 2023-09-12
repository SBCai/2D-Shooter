#pragma once

#include "FloatFunctor.h"
#include "Vec2.h"

// define a Consideration subclass which considers the closest cover distance
class CoverDistanceConsideration : public FloatFunctor
{
public:
  // takes in enemy's position
  CoverDistanceConsideration(Vec2 pos);

  // evaluate the cover
  float evaluate(const std::pair<Vec2, char> cover);

private:
  Vec2 m_Pos;
};
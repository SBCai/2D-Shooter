#pragma once

#include "FloatFunctor.h"
#include "Vec2.h"
#include <float.h>

// define a Consideration subclass which considers the cover that was not selected from the last selection
class CoverSelectedConsideration : public FloatFunctor
{
public:
  // takes in the previous cover position
  CoverSelectedConsideration(Vec2 pos) : previous_cover(pos) {};

  // evaluate the cover
  float evaluate(const std::pair<Vec2, char> cover);

private:
  Vec2 previous_cover;
};
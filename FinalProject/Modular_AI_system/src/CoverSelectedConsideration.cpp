#include "CoverSelectedConsideration.h"

// evaluate the cover
float CoverSelectedConsideration::evaluate(const std::pair<Vec2, char> cover) {
  // return -FLA_MAX if the cover was selected from the previous selection
  if (previous_cover == cover.first)
    return 0.0f;
   else
    return 1.0f;
}
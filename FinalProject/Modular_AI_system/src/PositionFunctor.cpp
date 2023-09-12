#include "PositionFunctor.h"

Vec2 PositionFunctor::evaluate(std::vector<std::pair<Vec2, char>> covers, std::vector<float> values)
{
  float max = -FLT_MAX;
  Vec2 position;
  // go through the vectors and check which vector has the highest value;
  for(int i = 0; i < covers.size(); i++) {
    if(values[i] > max) {
      max = values[i];
      position = covers[i].first;
    }
  }
  if ((int)max <= 1) {
    return Vec2(-1, -1);
  }
  return position;
}
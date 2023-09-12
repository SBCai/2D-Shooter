#include "CoverDistanceConsideration.h"

// initialize enemy's position
CoverDistanceConsideration::CoverDistanceConsideration(Vec2 pos) : m_Pos(pos) {}

float CoverDistanceConsideration::evaluate(const std::pair<Vec2, char> cover) {
  // extract the position of the cover
  Vec2 coverPos = cover.first;
  // get the distance between the enemy and the cover
  float distance = this->m_Pos.distSqr(coverPos);

  // return the reciprocal of the distance as we want the max number later
  return 1.0f/(distance + 1.0f);
}
#include "CoverOccupyConsideration.h"

// evaluate the cover
float CoverOccupyConsideration::evaluate(const std::pair<Vec2, char> cover) {
  Vec2 cover_pos = cover.first;
  // check if any enemy is using the cover
  for(Gunner* enemy : m_enemy) {
    Vec2 occupiedCover_pos = enemy->getDestPos();
    // return -FLT_MAX if the cover is occupied
    if (enemy->getHidden() && occupiedCover_pos == cover_pos) {
      return 0.0f;
    }

  }
  return 1.0f;
}
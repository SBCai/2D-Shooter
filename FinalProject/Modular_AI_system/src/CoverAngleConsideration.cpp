#include "CoverAngleConsideration.h"

// initialize player's position
CoverAngleConsideration::CoverAngleConsideration(Vec2 pos) : player_Pos(pos) {}

float CoverAngleConsideration::evaluate(const std::pair<Vec2, char> cover) {
  // extract the position of the cover
  Vec2 coverPos = cover.first;
  // extract the angle the cover can cover
  char angle = cover.second;

  // check the angle
  switch (angle) {
    // if the cover can cover enemy on top
    case 'u':
      // if player is on the bottom of the cover
      if (coverPos.y < this->player_Pos.y) {
        // the cover is good
        return 1.0f;
      // if player is on top if it
      } else {
        // we don't choose this cover
        return -9999.0f;
      }
      break;

    case 'd':
      // if player is on top of the cover
      if (coverPos.y > this->player_Pos.y) {
        // the cover is good
        return 1.0f;
      // if player is on the bottom if it
      } else {
        // we don't choose this cover
        return -9999.0f;
      }
      break;

    case 'l':
      // if player is on right of the cover
      if (coverPos.x < this->player_Pos.x) {
        // the cover is good
        return 1.0f;
      // if player is on the left if it
      } else {
        // we don't choose this cover
        return -9999.0f;
      }
      break;

    case 'r':
      // if player is on left of the cover
      if (coverPos.x > this->player_Pos.x) {
        // the cover is good
        return 1.0f;
      // if player is on the left if it
      } else {
        // we don't choose this cover
        return -9999.0f;
      }
      break;

      default:
        return -9999.0f;
  }
}
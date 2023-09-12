#include "Generator.h"

// takes in a game object and return all possible cover positions
std::vector<std::pair<Vec2, char>> Generator::generatePositions(Game& game) {
  std::vector<std::pair<Vec2, char>> allCover;
  // Iterate through all covers and generate positions to hide
  for(Cover* cover : game.getCovers()) {
    Vec2 position = cover->getPosition();
    int type = cover->getType();
    // if cover type is horizontal
    if(type) {
      // generate multiple positions for this cover
      for(int i = position.x; i < (int)(position.x + COVER_WIDTH); i += SHORT_GUNNER_SIZE) {
        // generate position slightly up of the cover
        Vec2 upPos((float)i + SHORT_GUNNER_SIZE, position.y - 0.5f);
        // generate a pair indicating the position cover enemy from (d)own
        std::pair<Vec2, char> up (upPos, 'u');
        // generate position slightly down of the cover
        Vec2 downPos((float)i + SHORT_GUNNER_SIZE, position.y + 0.5f);
        // generate a pair indicating the position cover enemy from (u)p
        std::pair<Vec2, char> down (downPos, 'd');
        allCover.push_back(up);
        allCover.push_back(down);
      }

    // if cover type is vertical
    } else {

      for(int i = position.y; i < (int)(position.y + COVER_WIDTH); i += SHORT_GUNNER_SIZE) {
        // generate position slightly left of the cover
        Vec2 leftPos(position.x - 0.5f, (float)i + SHORT_GUNNER_SIZE);
        // generate a pair indicating the position cover enemy from (r)ight
        std::pair<Vec2, char> left (leftPos, 'l');
        // generate position slightly down of the cover
        Vec2 rightPos(position.x + 0.5f, (float)i + SHORT_GUNNER_SIZE);
        // generate a pair indicating the position cover enemy from (l)eft
        std::pair<Vec2, char> right (rightPos, 'r');
        allCover.push_back(left);
        allCover.push_back(right);

      }
    }
  }

  return allCover;
}


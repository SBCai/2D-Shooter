#include "CoverToPlayerConsideration.h"

// evaluate covers that are in between enemy and player
float CoverToPlayerConsideration::evaluate(const std::pair<Vec2, char> cover) {
  Vec2 coverPos = cover.first;

  // if enemy is on the left side of the player
  if (enemy_Pos.x < player_Pos.x) {
    // if enemy is on top of a player
    if (enemy_Pos.y < player_Pos.y) {
      // if cover is in between of them
      if (coverPos.x > enemy_Pos.x && coverPos.x < player_Pos.x
       && coverPos.y > enemy_Pos.y && coverPos.y < player_Pos.y) {
        return 1.0f;
      } else {
        return 0.0f;
      }
    } else if (enemy_Pos.y > player_Pos.y) {
      // if cover is in between of them
      if (coverPos.x > enemy_Pos.x && coverPos.x < player_Pos.x
       && coverPos.y > player_Pos.y && coverPos.y < enemy_Pos.y) {
        return 1.0f;
      } else {
        return 0.0f;
      }
    // if enemy is align with player
    }
    else {
      // if cover is in between of them
        if (coverPos.x > enemy_Pos.x) {
          return 1.0f;
        } else {
          return 0.0f;
        }
    }

  // if enemy is on the right side of the player
  } else if (enemy_Pos.x > player_Pos.x) {
    // if enemy is on top of a player
    if (enemy_Pos.y < player_Pos.y) {
      // if cover is in between of them
      if (coverPos.x < enemy_Pos.x && coverPos.x > player_Pos.x
       && coverPos.y > enemy_Pos.y && coverPos.y < player_Pos.y) {
        return 1.0f;
      } else {
        return 0.0f;
      }
    // if enemy is on bottom of a player
    } else if (enemy_Pos.y > player_Pos.y) {
      // if cover is in between of them
      if (coverPos.x < enemy_Pos.x && coverPos.x > player_Pos.x
       && coverPos.y > player_Pos.y && coverPos.y < enemy_Pos.y) {
        return 1.0f;
      } else {
        return 0.0f;
      }
    // if enemy is align with player
    }  else {
      if (coverPos.x < enemy_Pos.x) {
        return 1.0f;
      } else {
        return 0.0f;
      }
    }
  // if enemy is align with player on the x
  } else {
    if (enemy_Pos.y < player_Pos.y) {
      if (coverPos.y > enemy_Pos.y) {
        return 1.0f;
      } else {
        return 0.0f;
      }
    } else {
      if (coverPos.y < enemy_Pos.y) {
        return 1.0f;
      } else {
        return 0.0f;
      }
    }
  }
}

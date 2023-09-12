#include "ShootAction.h"

// evaluate the priority of enemy to shoot
float ShootAction::evaluate() {
  // get the player's position
  Vec2 player_Pos = m_player->getPosition();
  // get the enemy's position
  Vec2 enemy_Pos = m_enemy->getPosition();

  // get left X between player and enemy
  float leftX = player_Pos.x >= enemy_Pos.x? enemy_Pos.x : player_Pos.x;
  // get right X between player and enemy
  float rightX = player_Pos.x >= enemy_Pos.x? player_Pos.x : enemy_Pos.x;
  // get top Y between player and enemy
  float topY = player_Pos.y >= enemy_Pos.y? enemy_Pos.y : player_Pos.y;
  // get bottom Y between player and enemy
  float bottomY = player_Pos.y >= enemy_Pos.y? player_Pos.y : enemy_Pos.y;
  // get the distance between enemy
  float distance = enemy_Pos.distSqr(player_Pos);

  // if player is within sight range of enemy
  if (distance < MAX_SIGHT) {
    // check if any cover blocks enemy to player
    for(Cover* cover : m_covers) {
        Vec2 cov_Position = cover->getPosition();
        int type = cover->getType();
        // if horizontal cover
        if(type) {
          if (cov_Position.y > topY && cov_Position.y < bottomY
           && cov_Position.x + COVER_WIDTH > leftX && cov_Position.x < rightX) {
            return 0.0f;
           }
        } else {
           if (cov_Position.x > leftX && cov_Position.x < rightX
            && cov_Position.y + COVER_WIDTH > topY && cov_Position.y < bottomY) {
             return 0.0f;
           }
        }
     }
     // return the distance + priority
     return MAX_SIGHT/distance + m_priority;
  }

  return MAX_SIGHT/distance;
}
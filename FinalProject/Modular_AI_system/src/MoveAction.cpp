#include "MoveAction.h"

// evaluate the enemy
float MoveAction::evaluate() {
  // if the enemy is current hidden
  if (m_enemy->getHidden()) {
    // get the time difference since hidden
    std::chrono::steady_clock::time_point now = std::chrono::steady_clock::now();
    float time_now = std::chrono::duration_cast<std::chrono::duration<float>>(now.time_since_epoch()).count();
    float timeSinceHidden = m_enemy->getTimeSinceHidden();

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

    // if hidden more than 3 sec
    float point;
    if (time_now - timeSinceHidden >= 3) {
      // return the priority to move
      point = 1.0f + m_priority;
    } else {
      // otherwise, keep hiding
      point = 0.0f;
    }

    // check if any cover blocks enemy to player
    for(Cover* cover : m_covers) {
        Vec2 cov_Position = cover->getPosition();
        int type = cover->getType();
        // if horizontal cover
        if(type) {
          if (cov_Position.y > topY && cov_Position.y < bottomY
           && cov_Position.x + COVER_WIDTH > leftX && cov_Position.x < rightX) {
            return point;
           }
        } else {
           if (cov_Position.x > leftX && cov_Position.x < rightX
            && cov_Position.y + COVER_WIDTH > topY && cov_Position.y < bottomY) {
             return point;
           }
        }
     }
  }

  return 1.0f + m_priority;
}
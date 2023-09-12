#include "Gunner.h"

// set the previous cover position (for enemy)
void Gunner::setPrevCoverPos(Vec2 pos) {
  prevCoverPos = pos;
}

// set the destination position (for enemy)
void Gunner::setDestPos(Vec2 pos) {
  destPos = pos;
  // when there's new dest pos, meaning enemy is on the move, so not hidden
  isHidden = false;
  // also hidden since reset
  timeSinceHidden = 0;
}


// shoot bullet (for player)
Bullet* Gunner::shootBullet() {
  Bullet* bullet;
  // set the bullet position
  Vec2 bullet_Pos = m_Pos;
  // check which direction bullet should move
  switch(m_direction) {
    // left
    case 'l':
      bullet = new Bullet(bullet_Pos, BULLET_SIZE, 0);
      bullet->setDestPos(0, m_Pos.y);
      break;
    // right
    case 'r':
      bullet = new Bullet(bullet_Pos, BULLET_SIZE, 0);
      bullet->setDestPos(GAME_GRID_WIDTH, m_Pos.y);
      break;
    // up
    case 'u':
      bullet = new Bullet(bullet_Pos, BULLET_SIZE, 0);
      bullet->setDestPos(m_Pos.x, 0);
      break;
    // down
    case 'd':
      bullet = new Bullet(bullet_Pos, BULLET_SIZE, 0);
      bullet->setDestPos(m_Pos.x, GAME_GRID_HEIGHT);
      break;
    // when direction is not set, up is default
    default:
      bullet = new Bullet(bullet_Pos, BULLET_SIZE, 0);
      bullet->setDestPos(m_Pos.x, 0);
      break;
  }
  return bullet;
}

// shoot bullet (for enemy)
Bullet* Gunner::enemyShootBullet(Vec2 player_Pos) {
  // get the center position of the player in the game graphic TODO
  Vec2 offSet = player_Pos + Vec2(SHORT_GUNNER_SIZE/2.0f, SHORT_GUNNER_SIZE/2.0f);
  // get the direction vec between enemy and player (for aiming)
  Vec2 directionVec = offSet - m_Pos;
  // set the directionVec to be longer so bullet can move to the end of map
  directionVec = directionVec * GAME_GRID_WIDTH;
  Bullet* bullet = new Bullet(m_Pos, BULLET_SIZE, 1);
  bullet->setDestPos(directionVec.x, directionVec.y);
  return bullet;
}

// tick function
void Gunner::tick(float deltaTSec) {
  move(deltaTSec);
}

// for enemy to move
void Gunner::move(float deltaTSec) {
    // Actually do the moving
    Vec2 moveVec = destPos - m_Pos;
    float distRemaining = moveVec.normalize();
    float moveDist = ENEMY_SPEED * deltaTSec;

    if (moveDist <= distRemaining)
    {
        m_Pos += moveVec * moveDist;
        // when the enemy arrive
        if (moveDist == distRemaining) {
           // set that cover position as the previous cover, so later we don't choose it again
           prevCoverPos = destPos;
           // hidden is true
           isHidden = true;
           // get the current time when enemy is hidden
           std::chrono::steady_clock::time_point now = std::chrono::steady_clock::now();
           timeSinceHidden = std::chrono::duration_cast<std::chrono::duration<float>>(now.time_since_epoch()).count();
        }
    }
    else
    {
        m_Pos += moveVec * distRemaining;
        prevCoverPos = destPos;
        isHidden = true;
        std::chrono::steady_clock::time_point now = std::chrono::steady_clock::now();
        timeSinceHidden = std::chrono::duration_cast<std::chrono::duration<float>>(now.time_since_epoch()).count();
    }

}
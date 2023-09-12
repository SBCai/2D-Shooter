#include "Bullet.h"

// bullet move
void Bullet::move(float deltaTSec) {
    // Actually do the moving
    Vec2 moveVec = destPos - m_Pos;
    float distRemaining = moveVec.normalize();
    float moveDist = BULLET_SPEED * deltaTSec;

    if (moveDist <= distRemaining)
    {
        m_Pos += moveVec * moveDist;
    }
    else
    {
        m_Pos += moveVec * distRemaining;
    }
}

// check if the bullet is out of map
bool Bullet::isOutOfMap() {
  return m_Pos.x <= 0 || m_Pos.x >= GAME_GRID_WIDTH || m_Pos.y <= 0 || m_Pos.y >= GAME_GRID_HEIGHT;
}

// check if the bullet hit the cover
bool Bullet::collideCover(std::vector<Cover*> covers) {
  // go through all covers
  for (Cover* cover : covers) {
    // get the cover position
    Vec2 cover_pos = cover->getPosition();
    // get the type of cover
    int type = cover->getType();
    // check if bullet hit them
    if(type) {
      if ((m_Pos.y + BULLET_SIZE > cover_pos.y
        && m_Pos.y < cover_pos.y + COVER_HEIGHT)
        && m_Pos.x + BULLET_SIZE > cover_pos.x && m_Pos.x < cover_pos.x + COVER_WIDTH) {
        return true;
       }
    } else {
      if ((m_Pos.x + BULLET_SIZE > cover_pos.x
        && m_Pos.x < cover_pos.x + COVER_HEIGHT)
        && m_Pos.y + BULLET_SIZE > cover_pos.y && m_Pos.y < cover_pos.y + COVER_WIDTH) {
        return true;
       }
    }
  }
  return false;
}

// check if bullet hit any enemy or player
bool Bullet::collideEntity(Vec2 other_pos, float other_size, int type) {
  // if bullet type is the same type of the entity, won't do damage
  if (m_type == type)
    return false;
  return (m_Pos.x + BULLET_SIZE/2.0f > other_pos.x - other_size/2.0f
       && m_Pos.x - BULLET_SIZE/2.0f < other_pos.x + other_size/2.0f
       && m_Pos.y + BULLET_SIZE/2.0f > other_pos.y - other_size/2.0f
       && m_Pos.y - BULLET_SIZE/2.0f < other_pos.y + other_size/2.0f);
}
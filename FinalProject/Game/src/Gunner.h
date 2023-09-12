#pragma once

#include "Constants.h"
#include "Vec2.h"
#include "Entity.h"
#include "Bullet.h"
#include <cmath>

// Gunner class that contains the info of player and enemy
class Gunner : public Entity {
public:
  // Gunner has position, health, type, and size
  Gunner(Vec2 pos, int health, int type, float size) : Entity(pos, size), m_health(health), m_type(type) {isHidden = false;}
  // return the health of the gunner
  int getHealth() {return m_health;}
  // take damage
  void getHit() {m_health = 0;}
  // return the type of the gunner (for enemy)
  int getType() {return m_type;}
  // tick function (for enemy)
  void tick(float deltaTSec);
  // move function (for enemy_ to move
  void move(float deltaTSec);
  // set the previous cover position (for enemy)
  void setPrevCoverPos(Vec2 pos);
  // get the previous cover position (for enemy)
  Vec2 getCoverPos() {return prevCoverPos;}
  // set the destination position (for enemy)
  void setDestPos(Vec2 pos);
  // get the destination position (for enemy)
  Vec2 getDestPos() {return destPos;}
  // get the direction (for player)
  char getDirection() {return m_direction;}
  // check if (for enemy) is hidden behind cover
  bool getHidden() {return isHidden;}
  // get the time when the enemy is hidden
  float getTimeSinceHidden() {return timeSinceHidden;}

  // shoot bullet (for player)
  Bullet* shootBullet();
  // shoot bullet (for enemy)
  Bullet* enemyShootBullet(Vec2 player_Pos);

  // move functions (for player)
  void moveLeft() {m_Pos += Vec2(-PLAYER_SPEED, 0.f);
                   m_direction = 'l';}
  void moveRight() {m_Pos += Vec2(PLAYER_SPEED, 0.f);
                    m_direction = 'r';}
  void moveUp() {m_Pos += Vec2(0.f, -PLAYER_SPEED);
                 m_direction = 'u';}
  void moveDown() {m_Pos += Vec2(0.f, PLAYER_SPEED);
                   m_direction = 'd';}

private:
  int m_health;
  int m_type;
  Vec2 destPos;
  Vec2 prevCoverPos;
  bool target;
  char m_direction;
  bool isHidden;
  float timeSinceHidden;
};

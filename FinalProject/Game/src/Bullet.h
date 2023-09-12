#pragma once

#include "Constants.h"
#include "Entity.h"
#include "Vec2.h"
#include "Cover.h"
#include <vector>

// bullet class
class Bullet : public Entity {
public:
  // bullet has position, size and type. type 1 -> enemy. type 2 -> player
  // bullet type with the same type as enemy/player won't do damage to enemy/player
  Bullet(Vec2 pos, float size, int type) : Entity(pos, size), m_type(type) {}
  // bullet move
  void move(float deltaTSec);
  // tick
  void tick(float deltaTSec) {move(deltaTSec);}
  // set the destination of the bullet
  void setDestPos(float x, float y) {destPos = Vec2(x,y);}
  // check if the bullet is out of map
  bool isOutOfMap();
  // check if the bullet hit the cover
  bool collideCover(std::vector<Cover*> covers);
  // check if bullet hit any enemy or player
  bool collideEntity(Vec2 other_pos, float other_size, int type);

private:
  Vec2 destPos;
  int m_type;
};
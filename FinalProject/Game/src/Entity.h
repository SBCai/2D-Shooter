#pragma once

#include "Constants.h"
#include "Vec2.h"

// entity class contain basic info of an entity
class Entity {
public:
  // an entity has position and size
  Entity(Vec2 pos, float size) : m_Pos(pos), m_size(size) {}

  // return the position of the entity
  Vec2 getPosition() {return m_Pos;}
  // return the size of the entity
  float getSize() {return m_size;}
  // tick
  virtual void tick(float deltaTSec) = 0;
  // move
  virtual void move(float deltaTSec) = 0;

protected:
  float m_size;
  Vec2 m_Pos;

};
#pragma once

#include "Vec2.h"

// Define a cover which has a position and a type: 1 -> horizontal and 0 -> vertical cover
class Cover
{
public:
  // a cover has a position and type
  Cover(const Vec2& pos, int type) : m_Pos(pos), m_type(type) {}
  // get the position of the cover
  Vec2 getPosition() {return m_Pos;}
  // get the type of the cover
  int getType() {return m_type;}

private:
  Vec2 m_Pos;
  int m_type;

};
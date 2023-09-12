#pragma once

#include "FloatFunctor.h"
#include "Vec2.h"
#include "Gunner.h"
#include "Action.h"

// Move action class that return the point for enemy to move
class MoveAction : public Action {
public:
  // takes in an enemy and the priority point
  MoveAction(Gunner* player, Gunner* enemy,  std::vector<Cover*> covers, float priority): m_player(player), m_enemy(enemy), m_covers(covers), m_priority(priority) {}
  // evaluate the enemy
  float evaluate();

private:
  Gunner* m_player;
  Gunner* m_enemy;
  std::vector<Cover*> m_covers;
  float m_priority;
};
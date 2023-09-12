#pragma once

#include "FloatFunctor.h"
#include "Vec2.h"
#include "Gunner.h"
#include "Cover.h"
#include "Action.h"
#include <vector>

//Shoot action class to evaluate the priority of enemy to shoot
class ShootAction : public Action{
public:

  // takes in a player, enemy, a list of cover and the priority point
  ShootAction(Gunner* player, Gunner* enemy, std::vector<Cover*> covers, float priority)
    : m_player(player), m_enemy(enemy), m_covers(covers), m_priority(priority) {}

  // evaluate the enemy
  float evaluate();

private:
  Gunner* m_player;
  Gunner* m_enemy;
  std::vector<Cover*> m_covers;
  float m_priority;
};



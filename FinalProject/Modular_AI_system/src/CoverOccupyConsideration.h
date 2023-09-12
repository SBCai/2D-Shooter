#pragma once

#include "FloatFunctor.h"
#include "Vec2.h"
#include "Constants.h"
#include "Gunner.h"
#include <float.h>

// class that considers the covers that are not occupied by enemy
class CoverOccupyConsideration : public FloatFunctor
{
  public:
    // takes in a list of enemy
    CoverOccupyConsideration(std::vector<Gunner*> enemy) : m_enemy(enemy) {};

    // evaluate the cover
    float evaluate(const std::pair<Vec2, char> cover);

  private:
    std::vector<Gunner*> m_enemy;
};
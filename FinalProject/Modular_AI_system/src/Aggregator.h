#pragma once

#include "FloatFunctor.h"
#include "Vec2.h"
#include <float.h>
#include <utility>
#include <vector>

// Base class for aggregators
class Aggregator {
public:
  // takes in a list of considerations
  Aggregator(std::vector<FloatFunctor* > considerations) : m_considerations(considerations) {}
  // sum all the points of considerations for a cover
  float evaluate();
  // set the cover to be evaluated
  void setCover(std::pair<Vec2, char> cover) {m_cover = cover;}

private:
  std::pair<Vec2, char> m_cover;
  std::vector<FloatFunctor* > m_considerations;

};
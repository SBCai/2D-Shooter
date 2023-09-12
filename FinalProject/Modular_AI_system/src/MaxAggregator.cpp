#include "MaxAggregator.h"

// evaluate a list of action and return the max point
float MaxAggregator::evaluate() {
  float maxPoint = -FLT_MAX;
  for (Action* action : m_action) {
    float action_point = action->evaluate();
    if (action_point > maxPoint) {
      maxPoint = action_point;
    }
  }
  return maxPoint;
}
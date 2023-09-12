#pragma once

#include "Action.h"
#include <vector>
#include <float.h>

// MaxAggregator class that evaluate the max point of a list of action
class MaxAggregator {
public:
  // takes in a list of action
  MaxAggregator(std::vector<Action*> action) : m_action(action) {}
  float evaluate();

private:
  std::vector<Action*> m_action;
};
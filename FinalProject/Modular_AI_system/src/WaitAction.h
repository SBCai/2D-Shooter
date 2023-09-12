#pragma once
#include "Action.h"

// Wait action class that does nothing
class WaitAction : public Action {
public:
  WaitAction() {}
  float evaluate() {return 1.0f;}
};
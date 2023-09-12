#pragma once

#include "Vec2.h"
#include <utility>
#include <float.h>

// Define a FloatFunctor class that evaluate a particular cover position
class FloatFunctor {
public:
    // evaluate a particular cover position and return its score
    virtual float evaluate(const std::pair<Vec2, char> cover) = 0;
    virtual ~FloatFunctor() {}
};
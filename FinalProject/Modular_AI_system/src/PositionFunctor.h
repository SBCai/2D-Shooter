#pragma once

#include "Vec2.h"
#include <vector>

// generate a position from a list of covers and the points of them
class PositionFunctor
{
public:
    Vec2 evaluate(std::vector<std::pair<Vec2, char>> covers, std::vector<float> values);
};
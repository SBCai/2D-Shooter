#pragma once

// Action class that return the score of an action
class Action {
public:
virtual ~Action() {}
virtual float evaluate() = 0;
};

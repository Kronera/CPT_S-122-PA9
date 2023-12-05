#pragma once
#include "base.h"

class Cannon : public Base {
public:
    Cannon(bool isred) : Base(isred) {
        _name = "cannon";
        //same order as cart.
        _captured_hierarchy = 2;
        //can capture anyone.
        _capturing_hierarchy = 9;
    }
};

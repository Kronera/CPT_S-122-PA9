#pragma once
#include "base.h"

class King : public Base {
public:
    King(bool isred) : Base(isred) {
        _name = "King";
        //can capture anyone but pawn.
        _captured_hierarchy = 8;
        //can only be captured by pawn.
        _capturing_hierarchy = 8;
    }
};

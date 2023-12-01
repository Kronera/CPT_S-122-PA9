#pragma once
#include "base.h"

class Pawn : public Base {
    public:
    Pawn(bool isred) : Base(isred) {
        _name = "pawn";
        _captured_hierarchy = 1;
        _capturing_hierarchy = 1;
    }
};
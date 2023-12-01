#pragma once
#include "base.h"

class Guard : public Base {
public:
    Guard(bool isred) : Base(isred) {
        _name = "guard";
        _captured_hierarchy = 5;
        _capturing_hierarchy = 5;
    }
};

#pragma once
#include "base.h"

class Elephant : public Base {
public:
    Elephant(bool isred) : Base(isred) {
        _name = "elephant";
        _captured_hierarchy = 4;
        _capturing_hierarchy = 4;
    }
};
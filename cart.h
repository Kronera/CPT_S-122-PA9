#pragma once
#include "base.h"

class Cart : public Base {
public:
    Cart(bool isred) : Base(isred) {
        _name = "cart";
        _captured_hierarchy = 3;
        _capturing_hierarchy = 3;
    }
};
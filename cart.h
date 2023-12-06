#pragma once
#include "base.h"

class Cart : public Base {
public:
    Cart(bool isred) : Base(isred) {
        _name = "cart";
        _captured_hierarchy = 3;
        _capturing_hierarchy = 3;
        redIcon.loadFromFile("Red Cart.png");
        blackIcon.loadFromFile("Black Cart.png");
        notRevTexture.loadFromFile("not rev.png");
        redSprite.setTexture(redIcon);
        blackSprite.setTexture(blackIcon);
        notRevSprite.setTexture(notRevTexture);
    }

};

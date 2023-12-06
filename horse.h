#pragma once
#include "base.h"

class Horse : public Base {
public:
    Horse(bool isred) : Base(isred) {
        _name = "horse";
        _captured_hierarchy = 2;
        _capturing_hierarchy = 2;
        redIcon.loadFromFile("Red Horse.png");
        blackIcon.loadFromFile("Black Horse.png");
        notRevTexture.loadFromFile("not rev.png");
        redSprite.setTexture(redIcon);
        blackSprite.setTexture(blackIcon);
        notRevSprite.setTexture(notRevTexture);
    }
};

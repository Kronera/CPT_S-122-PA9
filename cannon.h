#pragma once
#include "base.h"

class Cannon : public Base {
public:
    Cannon(bool isred) : Base(isred) {
        _name = "cannon";
        //same order as cart.
        _captured_hierarchy = 2;
        //can capture anyone.
        _capturing_hierarchy = 100;
        redIcon.loadFromFile("Red Cannon.png");
        blackIcon.loadFromFile("Black Cannon.png");

        redSprite.setTexture(redIcon);
        blackSprite.setTexture(blackIcon);
        notRevSprite.setTexture(notRevTexture);


    }
};

#pragma once
#include "base.h"

class Pawn : public Base {
public:
    Pawn(bool isred) : Base(isred) {
        _name = "pawn";
        _captured_hierarchy = 1;
        _capturing_hierarchy = 1;
        redIcon.loadFromFile("Red Pawn.png");
        blackIcon.loadFromFile("Black Pawn.png");
        notRevTexture.loadFromFile("not rev.png");
        redSprite.setTexture(redIcon);
        blackSprite.setTexture(blackIcon);
        notRevSprite.setTexture(notRevTexture);

    }
};

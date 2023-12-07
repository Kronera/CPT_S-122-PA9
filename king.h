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
        loadtexture();
    }

    void loadtexture(void) override {
        redIcon.loadFromFile("Red King.png");
        blackIcon.loadFromFile("Black King.png");
        notRevTexture.loadFromFile("not rev.png");
        redSprite.setTexture(redIcon);
        blackSprite.setTexture(blackIcon);
        notRevSprite.setTexture(notRevTexture);

    }
};

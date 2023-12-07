#pragma once
#include "base.h"

class Guard : public Base {
public:
    Guard(bool isred) : Base(isred) {
        _name = "guard";
        _captured_hierarchy = 5;
        _capturing_hierarchy = 5;
        loadtexture();
    }

    void loadtexture(void) override {
        blackIcon.loadFromFile("Black Guard.png");
        redIcon.loadFromFile("Red Guard.png");
        notRevTexture.loadFromFile("not rev.png");
        blackSprite.setTexture(blackIcon);
        redSprite.setTexture(redIcon);
        notRevSprite.setTexture(notRevTexture);
    }
};

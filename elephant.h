#pragma once
#include "base.h"

class Elephant : public Base {
public:
    Elephant(bool isred) : Base(isred) {
        _name = "elephant";
        _captured_hierarchy = 4;
        _capturing_hierarchy = 4;
        loadtexture();
    }

    void loadtexture(void) override {
        redIcon.loadFromFile("Red Elephant.png");
        blackIcon.loadFromFile("Black Elephant.png");
        notRevTexture.loadFromFile("not rev.png");
        redSprite.setTexture(redIcon);
        blackSprite.setTexture(blackIcon);
        notRevSprite.setTexture(notRevTexture);
    }
};

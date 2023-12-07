#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include "SFML/Graphics.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <array>
#include <list>
#include <cstdlib>
#include <time.h>
#include <chrono>
#include <thread>
#include <sstream>
#include <ctime>

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::ostream;
using std::ofstream;

class Base {
public:

    Base(bool isred) { // parameterized constructor
        _x = 0;
        _y = 0;
        _is_red = isred;
        _name = "default piece";
        _captured_hierarchy = 0;
        _capturing_hierarchy = 0;
        redIcon.loadFromFile("warning image.png");
        blackIcon.loadFromFile("warning image.png");

        redSprite.setTexture(redIcon);
        blackSprite.setTexture(blackIcon);
        constructorHelper();


    }
    // loads the unrevealed texture for all pieces
    void constructorHelper() {
        notRevTexture.loadFromFile("not rev.png");
        notRevSprite.setTexture(notRevTexture);
    }

    virtual ~Base(); // destructor

    // getters
    string getname() const {
        return _name;
    }
    bool isred() const {
        return _is_red;
    }
    int getX() const;
    int getY() const;
    int getdefense() {
        return _captured_hierarchy;
    }
    int isredn() {
        if (isred()) return 1;
        return 0;

    }
    int getpower() {
        return _capturing_hierarchy;
    }


    //poly function
    virtual void loadtexture(void){}


    // setters
    void setX(int num);
    void setY(int num);



    // textures
    sf::Sprite notRevSprite;
    sf::Sprite redSprite;
    sf::Sprite blackSprite;
    sf::Texture redIcon;
    sf::Texture blackIcon;
    sf::Texture notRevTexture;


protected:
    static double _radius;
    string _name;
    int _capturing_hierarchy;
    int _captured_hierarchy;
    bool _is_red;
    //position
    int _x;
    int _y;

private:
};

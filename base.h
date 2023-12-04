#pragma once
#define _CRT_SECURE_NO_WARNINGS

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
    Base(bool isred) {
        _x = 0;
        _y = 0;
        _is_red = isred;
        _name = "default piece";
        _captured_hierarchy = 0;
        _capturing_hierarchy = 0;
    }

    virtual ~Base();
    virtual void move(int x, int y);
    string getname() {
        return _name;
    } 
    //shortened for capturing hierachy.
    int getpower() {
        return _capturing_hierarchy;
    }

    //shortened for captured hierachy
    int getdefense() {
        return _captured_hierarchy;
    }

    bool isred() {
        return _is_red;
    }

    //returns isred but in number form (1 for true and otherwise)
    int isredn() {
        if (isred()) return 1;
        return 0;

    }


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

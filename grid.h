#pragma once
#include "base.h"

class Grid {
public:
    Grid() {
        revealed = false;
        _chess = nullptr;
    }

    ~Grid(){}

    void assign(Base* object) {
        _chess = object;
    }

    bool isEmpty() {
        if (_chess == nullptr) return true;
        return false;
    }

    Base* getchess() {
        return _chess;
    }

    void print(void) {
        if (_chess == nullptr) {
            cout << "empty grid ";
        }
        else {
            cout << _chess->getname() << " ";
        }
    }

private:
    Base* _chess;
    bool revealed;
};
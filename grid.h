#pragma once
#include "base.h"

class Grid {
public:
    Grid() {
        revealed = false;
        _chess = nullptr;
    }

    ~Grid() {}

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

    //this version prints the piece name if its revealed, and - if its not.
    void print(void) {
        if (_chess == nullptr) {
            cout << "== ";
        }
        else {
            if (revealed) {
                if (_chess->isred()) {
                    cout << "r" << _chess->getpower() << " ";
                }
                else {
                    cout << "b" << _chess->getpower() << " ";

                }
            }
            else {
                cout << "-- ";
            }
        }
    }

    //this version prints the piece name regardless if its revealed.
    void directprintname(void) {
        if (_chess == nullptr) {
            cout << "empty grid ";
        }
        else {
            cout << _chess->getname() << " ";
        }
    }

    void reveal(void) {
        revealed = true;
    }

    bool revealstatus(void) {
        return revealed;
    }

private:
    Base* _chess;
    bool revealed;
};
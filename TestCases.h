#pragma once
#include "grid.h"
#include "pawn.h"
#include "cart.h"
#include "horse.h"
#include "elephant.h"
#include "guard.h"
#include "king.h"
#include "cannon.h"

//we are going to test mostly on the function of the board, since the graphics and visuals are based on the main board's information
class Test {
public:
    Test() {

    }
    ~Test() {

    }

    void RunTestCases(void);



private:
};

//for convinence
void printline(void);

int getx(void);

int gety(void);

char getdirection(void);

bool swapturn(bool turn);

void printboard(Grid boards[][8]);
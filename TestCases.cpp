#include "TestCases.h"


//the test cases are set up as specific, unique situation that happen ingame that have a unique function/algroithem assoicated with them
//the user will still have to input actions but this is via console with SFML (graphics are implemented from console code) but the board
//will still be displayed for a better understanding
void Test::RunTestCases(void) {

    std::srand(std::time(0));

    Grid board[4][8];
    int index = 1, totalElements = 32, x = 0, y = 0, options = 0, isred = 0, player1color = -1, currentcolor = -1, placeholder = 0, interval1 = 0, interval2 = 0, intervalS = 0, intervalN = 0, intervalW = 0, intervalE = 0;
    bool isgameover = false, player1turn = false, South = false, North = false, East = false, West = false, southwalk = false, northwalk = false, eastwalk = false, westwalk = false;
    char userinput = '\0';
    int redpiecesleft = 0, blackpiecesleft = 0;
    int testcases;
    cout << "Enter an integer for the test case: " << endl;
    cout << "Testcase 1: test reveal" << endl;
    cout << "Testcase 2: test capturing with normal piece. (inputs: 1, 1, E) " << endl;
    cout << "Testcase 3: test capturing with king and pawn. (inputs: 1, 1, E) " << endl;
    cout << "Testcase 4: test capturing with cannon(long distance). (inputs: 1, 1, E) " << endl;
    cout << "Testcase 5: test capturing with cannon(short distance). (inputs: 1, 1, E) " << endl;
    cin >> testcases;

    // Perform actions based on the input
    switch (testcases) {
    case 1:
        //add all piece
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 8; ++j) {
                if (index <= 5) {
                    board[i][j].assign(new Pawn(true));
                }
                else if (index <= 10) {
                    board[i][j].assign(new Pawn(false));
                }
                else if (index <= 12) {
                    board[i][j].assign(new Cannon(true));
                }
                else if (index <= 14) {
                    board[i][j].assign(new Cannon(false));
                }
                else if (index <= 16) {
                    board[i][j].assign(new Horse(true));
                }
                else if (index <= 18) {
                    board[i][j].assign(new Horse(false));
                }
                else if (index <= 20) {
                    board[i][j].assign(new Cart(true));
                }
                else if (index <= 22) {
                    board[i][j].assign(new Cart(false));
                }
                else if (index <= 24) {
                    board[i][j].assign(new Elephant(true));
                }
                else if (index <= 26) {
                    board[i][j].assign(new Elephant(false));
                }
                else if (index <= 28) {
                    board[i][j].assign(new Guard(true));
                }
                else if (index <= 30) {
                    board[i][j].assign(new Guard(false));
                }
                else if (index <= 31) {
                    board[i][j].assign(new King(true));
                }
                else if (index <= 32) {
                    board[i][j].assign(new King(false));
                }


                index++;
            }
        }

        //shuffle the entire board.
        for (int i = totalElements - 1; i > 0; --i) {
            int j = std::rand() % (i + 1);

            int row_i = i / 8;
            int col_i = i % 8;
            int row_j = j / 8;
            int col_j = j % 8;

            std::swap(board[row_i][col_i], board[row_j][col_j]);
        }
        break;
    case 2:
        board[0][0].assign(new Pawn(false));
        board[0][1].assign(new Pawn(true));

        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 8; ++j) {
                board[i][j].reveal();
            }
        }
        break;
    case 3:
        board[0][0].assign(new Pawn(false));
        board[0][1].assign(new King(true));

        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 8; ++j) {
                board[i][j].reveal();
            }
        }
        break;
    case 4: 
        board[0][0].assign(new Cannon(false));
        board[0][1].assign(new Elephant(false));
        board[0][7].assign(new King(true));

        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 8; ++j) {
                board[i][j].reveal();
            }
        }
        break;
    case 5:
        board[0][0].assign(new Cannon(false));
        board[0][1].assign(new Elephant(false));
        board[0][2].assign(new King(true));

        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 8; ++j) {
                board[i][j].reveal();
            }
        }
        break;
    default:
        cout << "Invalid input. " << testcases << endl;
        break;
    }



    //visualize the board after shuffling.
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 8; ++j) {
            //board[i][j].directprintname();
        }
        //cout << endl;
    }

    /* just some info to keep track of.
        capturing hierachy, captured hierachy
        base: 0,0

        pawn: 1, 1
        cannon: 9(anyone), 2
        horse: 2, 2
        cart: 3, 3
        elephant, 4, 4
        guard: 5, 5
        king: 8(anyone but pawn), 8(only pawn.)

        everyone's capturing hierachy is unique, we will use that to display the pieces.
        (for simplicity, king is reduced to 8 and cannon is 9).
    */


    while (!isgameover) {
        player1color = 1;
        player1turn = false;

        //start of normal loop
        printline();
        printboard(board);
        printline();
        //display player color
        cout << "Player colors: ";
        if (player1color) {
            cout << "Player1: red" << ", Player2: black." << endl;
        }
        else {
            cout << "Player1: black" << ", Player2: red." << endl;
        }


        //set the player color to match the current player
        //is player1's turn
        if (player1turn) {
            currentcolor = player1color;
            cout << "Player1's turn. " << endl;
        }
        //is player2's turn
        else {
            cout << "Player2's turn. " << endl;
            //player1's color is red
            if (player1color) {
                //set movable color to black
                currentcolor = 0;
            }
            //player1's color is black
            else {
                //set movable color to red
                currentcolor = 1;
            }
        }

        //get input 
        x = getx();
        y = gety();


        //check if the move is valid, if invalid, the players are not switched.


        //invalid move
        //if the grid selected is empty.
        if (board[y][x].isEmpty()) {
            cout << "Invalid move: Empty grid!" << endl;
        }
        else {
            //the piece is hidden
            if (!(board[y][x].revealstatus())) {
                board[y][x].reveal();

                //Valid move, swap player's turn
                player1turn = swapturn(player1turn);
            }
            //if the piece is revealed, is the opposite color of the player
            else if (board[y][x].getchess()->isredn() != currentcolor) {
                cout << "Invalid move: Wrong color! " << endl;
            }
            //the piece is the same color as the players.
            else {
                printline();
                //display the possible options in directions

                //this is for non cannon pieces.
                //for now, we will treat cannon as a piece that can capture anyone but can be captured by anyone.
                if (!(board[y][x].getchess()->getpower() == 9)) {
                    //if there are no options to move, then its an invalid move.
                    options = 0;
                    South = false, North = false, West = false, East = false;
                    southwalk = false, northwalk = false, eastwalk = false, westwalk = false;
                    cout << "Available moves: " << endl;

                    //check South
                    //y is not at the top row already
                    if (!(y == 3)) {
                        if (!board[y + 1][x].isEmpty()) {
                            if (board[y + 1][x].revealstatus()) {
                                //if the piece is the opposite color and capturable
                                if (!(board[y + 1][x].getchess()->isredn() == currentcolor)) {
                                    //special case for king
                                    if (board[y][x].getchess()->getpower() == 8) {
                                        //is a king!
                                        //if it is not a pawn, then it is capturable.
                                        if (!(board[y + 1][x].getchess()->getpower() == 1)) {
                                            South = true;
                                            options++;
                                            cout << "South" << endl;
                                        }
                                    }
                                    //special case for pawn
                                    else if (board[y][x].getchess()->getpower() == 1) {
                                        //is only valid if its another pawn OR a king.
                                        if (board[y + 1][x].getchess()->getpower() == 8 || board[y + 1][x].getchess()->getpower() == 1) {
                                            South = true;
                                            options++;
                                            cout << "South" << endl;
                                        }
                                    }
                                    else {
                                        if (board[y][x].getchess()->getpower() >= board[y + 1][x].getchess()->getdefense()) {
                                            South = true;
                                            options++;
                                            cout << "South" << endl;
                                        }
                                    }



                                }
                            }
                        }
                        else {
                            //that spot IS empty.
                            southwalk = true;
                            options++;
                            cout << "South (walk)" << endl;

                        }
                    }
                    //LETS REPEAT THIS 3 MORE TIMES

                    //North
                    if (!(y == 0)) {
                        //if its not empty
                        if (!board[y - 1][x].isEmpty()) {
                            if (board[y - 1][x].revealstatus()) {
                                //if the piece is the opposite color and capturable
                                if (!(board[y - 1][x].getchess()->isredn() == currentcolor)) {
                                    //special case for king
                                    if (board[y][x].getchess()->getpower() == 8) {
                                        //is a king!
                                        //if it is not a pawn, then it is capturable.
                                        if (!(board[y - 1][x].getchess()->getpower() == 1)) {
                                            North = true;
                                            options++;
                                            cout << "North" << endl;
                                        }
                                    }
                                    //special case for pawn
                                    else if (board[y][x].getchess()->getpower() == 1) {
                                        //is only valid if its another pawn OR a king.
                                        if (board[y - 1][x].getchess()->getpower() == 8 || board[y - 1][x].getchess()->getpower() == 1) {
                                            North = true;
                                            options++;
                                            cout << "North" << endl;
                                        }
                                    }
                                    else {
                                        if (board[y][x].getchess()->getpower() >= board[y - 1][x].getchess()->getdefense()) {
                                            North = true;
                                            options++;
                                            cout << "North" << endl;
                                        }
                                    }


                                }
                            }
                        }
                        else {
                            //that spot IS empty.
                            northwalk = true;
                            options++;
                            cout << "North (walk)" << endl;
                        }
                    }

                    //West
                    if (!(x == 0)) {
                        //if its not empty
                        if (!board[y][x - 1].isEmpty()) {
                            if (board[y][x - 1].revealstatus()) {
                                //if the piece is the opposite color and capturable
                                if (!(board[y][x - 1].getchess()->isredn() == currentcolor)) {
                                    //special case for king
                                    if (board[y][x].getchess()->getpower() == 8) {
                                        //is a king!
                                        //if it is not a pawn, then it is capturable.
                                        if (!(board[y][x - 1].getchess()->getpower() == 1)) {
                                            West = true;
                                            options++;
                                            cout << "West" << endl;
                                        }
                                    }
                                    //special case for pawn
                                    else if (board[y][x].getchess()->getpower() == 1) {
                                        //is only valid if its another pawn OR a king.
                                        if (board[y][x - 1].getchess()->getpower() == 8 || board[y][x - 1].getchess()->getpower() == 1) {
                                            West = true;
                                            options++;
                                            cout << "West" << endl;
                                        }
                                    }
                                    else {
                                        if (board[y][x].getchess()->getpower() >= board[y][x - 1].getchess()->getdefense()) {
                                            West = true;
                                            options++;
                                            cout << "West" << endl;
                                        }
                                    }

                                }
                            }
                        }
                        else {
                            //that spot IS empty.
                            westwalk = true;
                            options++;
                            cout << "west (walk)" << endl;
                        }
                    }

                    //East
                    if (!(x == 7)) {
                        //if its not empty
                        if (!board[y][x + 1].isEmpty()) {
                            if (board[y][x + 1].revealstatus()) {
                                //if the piece is the opposite color and capturable
                                if (!(board[y][x + 1].getchess()->isredn() == currentcolor)) {
                                    //special case for king
                                    if (board[y][x].getchess()->getpower() == 8) {
                                        //is a king!
                                        //if it is not a pawn, then it is capturable.
                                        if (!(board[y][x + 1].getchess()->getpower() == 1)) {
                                            East = true;
                                            options++;
                                            cout << "East" << endl;
                                        }
                                    }
                                    //special case for pawn
                                    else if (board[y][x].getchess()->getpower() == 1) {
                                        //is only valid if its another pawn OR a king.
                                        if (board[y][x + 1].getchess()->getpower() == 8 || board[y][x + 1].getchess()->getpower() == 1) {
                                            East = true;
                                            options++;
                                            cout << "East" << endl;
                                        }
                                    }
                                    else {
                                        if (board[y][x].getchess()->getpower() >= board[y][x + 1].getchess()->getdefense()) {
                                            East = true;
                                            options++;
                                            cout << "East" << endl;
                                        }
                                    }

                                }
                            }
                        }
                        else {
                            //that spot IS empty.
                            eastwalk = true;
                            options++;
                            cout << "east (walk)" << endl;
                        }
                    }

                    //there is no possible move.
                    if (options == 0) {
                        cout << "Invalid move : no possible moves" << endl;
                        userinput = '\0';
                    }
                    else {
                        userinput = '\0';
                        userinput = getdirection();
                    }

                    userinput = tolower(userinput);
                    if (userinput == 's' && South) {
                        delete board[y + 1][x].getchess();
                        board[y + 1][x].assign(board[y][x].getchess());
                        board[y][x].assign(nullptr);

                        //Valid move, swap player's turn
                        player1turn = swapturn(player1turn);
                    }
                    else if (userinput == 'n' && North) {
                        delete board[y - 1][x].getchess();
                        board[y - 1][x].assign(board[y][x].getchess());
                        board[y][x].assign(nullptr);

                        //Valid move, swap player's turn
                        player1turn = swapturn(player1turn);
                    }
                    else if (userinput == 'w' && West) {
                        delete board[y][x - 1].getchess();
                        board[y][x - 1].assign(board[y][x].getchess());
                        board[y][x].assign(nullptr);

                        //Valid move, swap player's turn
                        player1turn = swapturn(player1turn);

                    }
                    else if (userinput == 'e' && East) {
                        delete board[y][x + 1].getchess();
                        board[y][x + 1].assign(board[y][x].getchess());
                        board[y][x].assign(nullptr);

                        //Valid move, swap player's turn
                        player1turn = swapturn(player1turn);

                    }
                    else if (userinput == 's' && southwalk) {

                        board[y + 1][x].assign(board[y][x].getchess());
                        board[y][x].assign(nullptr);

                        //Valid move, swap player's turn
                        player1turn = swapturn(player1turn);

                    }
                    else if (userinput == 'n' && northwalk) {
                        board[y - 1][x].assign(board[y][x].getchess());
                        board[y][x].assign(nullptr);

                        //Valid move, swap player's turn
                        player1turn = swapturn(player1turn);

                    }
                    else if (userinput == 'w' && westwalk) {
                        board[y][x - 1].assign(board[y][x].getchess());
                        board[y][x].assign(nullptr);

                        //Valid move, swap player's turn
                        player1turn = swapturn(player1turn);

                    }
                    else if (userinput == 'e' && eastwalk) {
                        board[y][x + 1].assign(board[y][x].getchess());
                        board[y][x].assign(nullptr);

                        //Valid move, swap player's turn
                        player1turn = swapturn(player1turn);

                    }

                }
                else {
                    //this is for cannon.
                    options = 0;
                    South = false, North = false, West = false, East = false;
                    southwalk = false, northwalk = false, westwalk = false, eastwalk = false;
                    cout << "Available moves: " << endl;

                    //check South
                    //cannon needs atleast 2 space to move. 
                    if (((y + 2) >= 0)) {
                        //interval needs to be atlesat 1
                        interval1 = 1;
                        intervalS = 1;

                        //go to next solid piece.
                        while (board[y + interval1][x].isEmpty() && ((y + interval1) <= 3)) {
                            interval1++;
                        } //go to next non empty piece
                        intervalS = interval1 + 1;
                        while (board[y + intervalS][x].isEmpty() && ((y + intervalS) <= 3)) {
                            intervalS++;
                        }
                        //condition 1: either interval cannot be out of bound
                        //condition 2: second piece has to be an opposite color
                        if ((y + intervalS) <= 3 && (y + interval1) <= 3) {
                            if (board[y + intervalS][x].getchess()->isredn() != currentcolor) {
                                South = true;
                                options++;
                                cout << "South" << endl;
                            }
                        }
                    }


                    //check North
                    //cannon needs atleast 2 space to move. 
                    if (((y - 2) >= 0)) {
                        //interval needs to be atlesat 1
                        interval1 = 1;
                        intervalN = 1;

                        //go to next solid piece.
                        while (board[y - interval1][x].isEmpty() && ((y - interval1) >= 0)) {
                            interval1++;
                        } //go to next non empty piece
                        intervalN = interval1 + 1;
                        while (board[y - intervalN][x].isEmpty() && ((y - intervalN) >= 0)) {
                            intervalN++;
                        }
                        //condition 1: either interval cannot be out of bound
                        //condition 2: second piece has to be an opposite color
                        if ((y - intervalN) >= 0 && (y - interval1) >= 0) {
                            if (board[y - intervalN][x].getchess()->isredn() != currentcolor) {
                                North = true;
                                options++;
                                cout << "North" << endl;
                            }
                        }
                    }


                    //check West
                    //cannon needs atleast 2 space to move. 
                    if (((x - 2) >= 0)) {
                        //interval needs to be atlesat 1
                        interval1 = 1;
                        intervalW = 1;

                        //go to next solid piece.
                        while (board[y][x - interval1].isEmpty() && ((x - interval1) >= 0)) {
                            interval1++;
                        } //go to next non empty piece
                        intervalW = interval1 + 1;
                        while (board[y][x - intervalW].isEmpty() && ((x - intervalW) >= 0)) {
                            intervalW++;
                        }
                        //condition 1: either interval cannot be out of bound
                        //condition 2: second piece has to be an opposite color
                        if ((x - intervalW) >= 0 && (x - interval1) >= 0) {
                            if (board[y][x - intervalW].getchess()->isredn() != currentcolor) {
                                West = true;
                                options++;
                                cout << "West" << endl;
                            }
                        }
                    }

                    if (((x + 2) >= 0)) {
                        //interval needs to be atlesat 1
                        interval1 = 1;
                        intervalE = 1;

                        //go to next solid piece.
                        while (board[y][x + interval1].isEmpty() && ((x + interval1) <= 8)) {
                            interval1++;
                        } //go to next non empty piece
                        intervalE = interval1 + 1;
                        while (board[y][x + intervalE].isEmpty() && ((x + intervalE) <= 8)) {
                            intervalE++;
                        }
                        //condition 1: either interval cannot be out of bound
                        //condition 2: second piece has to be an opposite color
                        if ((x + intervalE) <= 8 && (x + interval1) <= 8) {
                            if (board[y][x + intervalE].getchess()->isredn() != currentcolor) {
                                East = true;
                                options++;
                                cout << "East" << endl;
                            }
                        }
                    }

                    if (!South && board[y + 1][x].isEmpty() && (y + 1) <= 3) {
                        southwalk = true;
                        options++;
                        cout << "south (walk)" << endl;
                    }
                    else if (!North && board[y - 1][x].isEmpty() && (y - 1) >= 0) {
                        northwalk = true;
                        options++;
                        cout << "north (walk)" << endl;
                    }
                    else if (!East && board[y][x + 1].isEmpty() && (x + 1) <= 8) {
                        eastwalk = true;
                        options++;
                        cout << "east (walk)" << endl;
                    }
                    else if (!West && board[y][x - 1].isEmpty() && (x - 1) >= 0) {
                        westwalk = true;
                        options++;
                        cout << "west (walk)" << endl;
                    }


                    //there is no possible move.
                    if (options == 0) {
                        cout << "Invalid move : no possible moves" << endl;
                        userinput = '\0';
                    }
                    else {
                        userinput = '\0';
                        userinput = getdirection();
                    }

                    userinput = tolower(userinput);
                    if (userinput == 's' && South) {
                        delete board[y + intervalS][x].getchess();
                        board[y + intervalS][x].assign(board[y][x].getchess());
                        board[y][x].assign(nullptr);

                        //Valid move, swap player's turn
                        if (player1turn) {
                            player1turn = false;
                        }
                        else {
                            player1turn = true;
                        }
                    }
                    else if (userinput == 'n' && North) {
                        delete board[y - intervalN][x].getchess();
                        board[y - intervalN][x].assign(board[y][x].getchess());
                        board[y][x].assign(nullptr);

                        //Valid move, swap player's turn
                        if (player1turn) {
                            player1turn = false;
                        }
                        else {
                            player1turn = true;
                        }
                    }
                    else if (userinput == 'w' && West) {
                        delete board[y][x - intervalW].getchess();
                        board[y][x - intervalW].assign(board[y][x].getchess());
                        board[y][x].assign(nullptr);

                        //Valid move, swap player's turn
                        if (player1turn) {
                            player1turn = false;
                        }
                        else {
                            player1turn = true;
                        }
                    }
                    else if (userinput == 'e' && East) {
                        delete board[y][x + intervalE].getchess();
                        board[y][x + intervalE].assign(board[y][x].getchess());
                        board[y][x].assign(nullptr);

                        //Valid move, swap player's turn
                        if (player1turn) {
                            player1turn = false;
                        }
                        else {
                            player1turn = true;
                        }
                    }
                    else if (userinput == 's' && southwalk) {

                        board[y + 1][x].assign(board[y][x].getchess());
                        board[y][x].assign(nullptr);

                        //Valid move, swap player's turn
                        player1turn = swapturn(player1turn);

                    }
                    else if (userinput == 'n' && northwalk) {
                        board[y - 1][x].assign(board[y][x].getchess());
                        board[y][x].assign(nullptr);

                        //Valid move, swap player's turn
                        player1turn = swapturn(player1turn);

                    }
                    else if (userinput == 'w' && westwalk) {
                        board[y][x - 1].assign(board[y][x].getchess());
                        board[y][x].assign(nullptr);

                        //Valid move, swap player's turn
                        player1turn = swapturn(player1turn);

                    }
                    else if (userinput == 'e' && eastwalk) {
                        board[y][x + 1].assign(board[y][x].getchess());
                        board[y][x].assign(nullptr);

                        //Valid move, swap player's turn
                        player1turn = swapturn(player1turn);

                    }



                }




            }



        }
        printline();

        redpiecesleft = 0;
        blackpiecesleft = 0;
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 8; ++j) {
                if (!board[i][j].isEmpty()) {
                    if (board[i][j].getchess()->isred()) {
                        redpiecesleft++;
                    }
                    if (!board[i][j].getchess()->isred()) {
                        blackpiecesleft++;
                    }
                }
            }
        }
        if (blackpiecesleft == 0) {
            cout << "BLACK SIDE WON. PIECES LEFT: " << blackpiecesleft << endl;
            isgameover = true;
        }
        else if (redpiecesleft == 0) {
            cout << "RED SIDE WON. PIECES LEFT: " << redpiecesleft << endl;
            isgameover = true;
        }



    }

    if (testcases == 1) {
        printline();
        printboard(board);
        printline();
        if (board[y][x].revealstatus()) {
            cout << "testcase 1: revealing a piece is successful." << endl;
        }
        else {
            cout << "testcase 1 failed to reveal said piece." << endl;
        }

    }
    else if (testcases == 2) {
        printline();
        printboard(board);
        printline();

        int numpawnleft = 0;
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 8; ++j) {
                if (!board[i][j].isEmpty()) {
                    if (board[i][j].getchess()->getpower() == 1 && board[i][j].getchess()->isred()) {
                        numpawnleft++;
                    }
                }
            }
        }

        if (numpawnleft == 0) {
            cout << "testcase 2: capturing a piece success." << endl;
        }
        else {
            cout << "testcase 2: capturing a piece failed." << endl;
        }
    }
    else if (testcases == 3) {
        printline();
        printboard(board);
        printline();

        int numkingleft = 0;
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 8; ++j) {
                if (!board[i][j].isEmpty()) {
                    if (board[i][j].getchess()->getpower() == 8) {
                        numkingleft++;
                    }
                }
            }
        }

        if (numkingleft == 0) {
            cout << "testcase 3: pawn capturing king success." << endl;
        }
        else {
            cout << "testcase 3: pawn capturing king failed." << endl;
        }
    }
    else if (testcases == 4) {

        printline();
        printboard(board);
        printline();

        int numkingleft = 0;
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 8; ++j) {
                if (!board[i][j].isEmpty()) {
                    if (board[i][j].getchess()->getpower() == 8) {
                        numkingleft++;
                    }
                }
            }
        }

        if (numkingleft == 0) {
            cout << "testcase 4: cannon capturing success." << endl;
        }
        else {
            cout << "testcase 4: cannon capturing failed." << endl;
        }
    }
    else if (testcases == 5) {

        printline();
        printboard(board);
        printline();

        int numkingleft = 0;
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 8; ++j) {
                if (!board[i][j].isEmpty()) {
                    if (board[i][j].getchess()->getpower() == 8) {
                        numkingleft++;
                    }
                }
            }
        }

        if (numkingleft == 0) {
            cout << "testcase 5: cannon capturing success." << endl;
        }
        else {
            cout << "testcase 5: cannon capturing failed." << endl;
        }
    }



}


//convinences
char getdirection(void) {
    char direction;

    do {
        cout << "Enter a direction (S, E, W, N, or Q): " << endl;
        cin >> direction;
        direction = toupper(direction);

        if (direction != 'S' && direction != 'E' && direction != 'W' && direction != 'N' && direction != 'Q') {
            cout << "Invalid direction. Please enter S, E, W, N, or Q." << endl;
        }
    } while (direction != 'S' && direction != 'E' && direction != 'W' && direction != 'N' && direction != 'Q');

    return direction;
}

int gety(void) {
    //get y
    int y = 0;
    do {
        // Prompt the user for input
        cout << "Now enter the y position of your first move." << endl;

        // Get the user's input
        std::cin >> y;

        // Check if the input is within the valid range
        if (y < 1 || y > 4) {
            cout << "Invalid input. Please enter a number between 1 and 4.\n";
        }

    } while (y < 1 || y > 4);
    y--;
    return y;
}

int getx(void) {
    //get x
    int x = 0;
    do {
        // Prompt the user for input
        cout << "Enter the x position of your first move." << endl;

        // Get the user's input
        std::cin >> x;

        // Check if the input is within the valid range
        if (x < 1 || x > 8) {
            cout << "Invalid input. Please enter a number between 1 and 8.\n";
        }
    } while (x < 1 || x > 8);
    x--;
    return x;
}

void printline(void) {
    cout << "------------------------------------------------" << endl;
}

bool swapturn(bool turn) {
    if (turn) {
        return false;
    }
    else {
        return true;
    }
}

void printboard(Grid boards[][8]) {
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 8; ++j) {
            boards[i][j].print();
        }
        cout << endl;
    }
}



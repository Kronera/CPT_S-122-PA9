#include <SFML/Graphics.hpp>
#include "grid.h"
#include "pawn.h"
#include "cart.h"
#include "horse.h"
#include "elephant.h"
#include "guard.h"
#include "king.h"
#include "cannon.h"

void visualizeBoard(Grid board[4][8], sf::RenderWindow& window, sf::Texture& boardTexture, sf::Sprite& bg) {
    
    //visualize the board after shuffling.
    window.clear();
    boardTexture.loadFromFile("board.png"); //load jpg
    bg.setTexture(boardTexture); //set sprite to board jpg
    window.draw(bg);
    
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 8; ++j) {
            int tempX, tempY;
            if (board[i][j].getchess()->getX() == 0 || board[i][j].getchess()->getY() == 0) {
                board[i][j].getchess()->setX(26 + (j * 98));
                board[i][j].getchess()->setY(20 + (i * 99));
            }
            tempX = board[i][j].getchess()->getX();
            tempY = board[i][j].getchess()->getY();
            board[i][j].reveal();
            if (board[i][j].revealstatus() == true) {
                if (board[i][j].getchess()->isred() == true) {
                    board[i][j].getchess()->redSprite.setPosition(sf::Vector2f(tempX, tempY));
                    window.draw(board[i][j].getchess()->redSprite);
                }
                else if (board[i][j].getchess()->isred() == false) {
                    board[i][j].getchess()->blackSprite.setPosition(sf::Vector2f(tempX, tempY));
                    window.draw(board[i][j].getchess()->blackSprite);
                }
            }
            else {
                board[i][j].getchess()->notRevSprite.setPosition(sf::Vector2f(tempX, tempY));
                window.draw(board[i][j].getchess()->notRevSprite);

            }

        }
        cout << endl;
    }
    
    window.display();
}

void printboard(Grid boards[][8]) {
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 8; ++j) {
            boards[i][j].print();
        }
        cout << endl;
    }
}

void printline(void) {
    cout << "------------------------------------------------" << endl;
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

bool swapturn(bool turn) {
    if (turn) {
        return false;
    }
    else {
        return true;
    }
}

int main() {
    int val = 0;
    Menu* menu = new Menu();
    menu->run_menu();
    val = menu->opt;
    delete menu;
    menu = nullptr;
    //Border
    if (val == 1)
    {
        sf::RenderWindow window(sf::VideoMode(800, 400), "BANQI!"); // create new window

        sf::Texture* board;
        sf::Sprite* bg;

        board = new sf::Texture();
        bg = new sf::Sprite();

        board->loadFromFile("./Board.jpg"); //load jpg
        bg->setTexture(*board); //set sprite to board jpg

        while (window.isOpen()) // loop while open
        {
            sf::Event event;
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed) { // conditional
                    window.close();
                }
            }

            window.clear();
            window.draw(*bg); //draw board WIP
            window.display();
        }
    }


    Grid board[4][8];
    int index = 1, totalElements = 32, x = 0, y = 0, options = 0, isred = 0;
    //-1 if not decided, 1 if its red, 0 if its black.
    int player1color = -1, currentcolor = -1, placeholder = 0, interval1 = 0, interval2 = 0;
    std::srand(std::time(0));
    bool isgameover = false, player1turn = false;
    //this is for the valid moves in South West East and North cordinates
    /*   N
       W   E
         S
    */
    bool South = false, North = false, East = false, West = false;
    bool southwalk = false, northwalk = false, eastwalk = false, westwalk = false;
    int intervalS = 0, intervalN = 0, intervalW = 0, intervalE = 0;
    char userinput = '\0';

    //initialize the board by putting in pieces in order.
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

        // Swap elements
        std::swap(board[row_i][col_i], board[row_j][col_j]);
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
        //first move, any move in this step should be valid.
        if (player1color == -1) {
            cout << "player 1 moving." << endl;
            printline();
            x = getx();
            y = gety();
            //we set the player's playing color here.
            player1color = (board[y][x].getchess()->isred()) ? 1 : 0;
            board[y][x].reveal();
            //second player's turn.
            player1turn = false;
            for (int i = 0; i < 4; ++i) {
                for (int j = 0; j < 8; ++j) {
                    board[i][j].reveal();
                }
            }
        }
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

                    } else if (userinput == 's' && southwalk) {

                        board[y + 1][x].assign(board[y][x].getchess());
                        board[y][x].assign(nullptr);

                        //Valid move, swap player's turn
                        player1turn = swapturn(player1turn);

                    } else if (userinput == 'n' && northwalk){
                        board[y - 1][x].assign(board[y][x].getchess());
                        board[y][x].assign(nullptr);

                        //Valid move, swap player's turn
                        player1turn = swapturn(player1turn);
                    
                    } else if (userinput == 'w' && westwalk) {
                        board[y][x-1].assign(board[y][x].getchess());
                        board[y][x].assign(nullptr);

                        //Valid move, swap player's turn
                        player1turn = swapturn(player1turn);

                    } else if (userinput == 'e' && eastwalk) {
                        board[y][x+1].assign(board[y][x].getchess());
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

                    if (!South && board[y+1][x].isEmpty() && (y+1) <= 3) {
                        southwalk = true;
                        options++;
                        cout << "south (walk)" << endl;
                    } else if(!North && board[y - 1][x].isEmpty() && (y-1) >= 0) {
                        northwalk = true;
                        options++;
                        cout << "north (walk)" << endl;
                    } else if (!East && board[y][x+1].isEmpty() && (x+1) <= 8) {
                        eastwalk = true;
                        options++;
                        cout << "east (walk)" << endl;
                    } else if (!West && board[y][x-1].isEmpty() && (x-1) >= 0) {
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
                    } else if (userinput == 's' && southwalk) {

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


    }


    //cleaning up the board after the game is finished.
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 8; ++j) {
            if (!(board[i][j].isEmpty())) {
                delete board[i][j].getchess();
                board[i][j].assign(nullptr);
            }
        }
        cout << endl;
    }

    return 0;
}

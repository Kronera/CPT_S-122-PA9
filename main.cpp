#include <SFML/Graphics.hpp>
#include "grid.h"
#include "pawn.h"
#include "cart.h"
#include "horse.h"
#include "elephant.h"
#include "guard.h"
#include "king.h"
#include "cannon.h"

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


    Grid board[4][8];
    int index = 1, totalElements = 32, x = 0, y = 0, options = 0, isred = 0;
    //-1 if not decided, 1 if its red, 0 if its black.
    int player1color = -1, currentcolor = -1;
    std::srand(std::time(0));
    //
    bool isgameover = false, player1turn = false;


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
            board[i][j].directprintname();
        }
        cout << endl;
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
                if (player1turn) {
                    player1turn = false;
                }
                else {
                    player1turn = true;
                }
            }  
            //if the piece is revealed, is the opposite color of the player
            else if (board[y][x].getchess()->isredn() != currentcolor) {
                cout << "Invalid move: Wrong color! " << endl;
            }
            //the piece is the same color as the players.
            else {
                printline();
                //display the possible options in direction in x,y cordinates (1,0) = right, (-1,0) = left, (0,1) = up, (0,-1) = down
                //this is for non cannon pieces.
                
                
                //if there are no options to move, then its an invalid move.
                options = 0;
                cout << "Available moves: " << endl;

                //check top
                //y is not at the top row already
                if (!(y == 0)) {
                    //if its not empty
                    if (!(board[y][x].isEmpty())) {
                        //if the piece is the opposite color and capturable
                        if (!(board[y - 1][x].getchess()->isredn() == currentcolor)) {
                            //special case for king
                            if (board[y][x].getchess()->getpower() == 8) {
                                //is a king!
                                //if it is not a pawn, then it is capturable.
                                if (!(board[y - 1][x].getchess()->getpower() == 1)) {
                                    options++;
                                    cout << "(0,1)" << endl;
                                }
                            }
                            //special case for pawn
                            else if (board[y][x].getchess()->getpower() == 1) {
                                //is only valid if its another pawn OR a king.
                                if (board[y - 1][x].getchess()->getpower() == 8 || board[y - 1][x].getchess()->getpower() == 1) {
                                    options++;
                                    cout << "(0,1)" << endl;
                                }
                            }
                            else {
                                if (board[y][x].getchess()->getpower() >= board[y-1][x].getchess()->getdefense()) {
                                    options++;
                                    cout << "(0,1)" << endl;
                                }
                            }

                            //if it reached here, it is invalid.




                        }
                    }
                }
                //LETS REPEAT THIS 3 MORE TIMES

                //down
                if (!(y == 3)) {
                    //if its not empty
                    if (!(board[y][x].isEmpty())) {
                        //if the piece is the opposite color and capturable
                        if (!(board[y+1][x].getchess()->isredn() == currentcolor)) {
                            //special case for king
                            if (board[y][x].getchess()->getpower() == 8) {
                                //is a king!
                                //if it is not a pawn, then it is capturable.
                                if (!(board[y + 1][x].getchess()->getpower() == 1)) {
                                    options++;
                                    cout << "(0,-1)" << endl;
                                }
                            }
                            //special case for pawn
                            else if (board[y][x].getchess()->getpower() == 1) {
                                //is only valid if its another pawn OR a king.
                                if (board[y + 1][x].getchess()->getpower() == 8 || board[y + 1][x].getchess()->getpower() == 1) {
                                    options++;
                                    cout << "(0,-1)" << endl;
                                }
                            }
                            else {
                                if (board[y][x].getchess()->getpower() >= board[y + 1][x].getchess()->getdefense()) {
                                    options++;
                                    cout << "(0,-1)" << endl;
                                }
                            }

                            //if it reached here, it is invalid.




                        }
                    }
                }

                //left
                if (!(x == 0)) {
                    //if its not empty
                    if (!(board[y][x].isEmpty())) {
                        //if the piece is the opposite color and capturable
                        if (!(board[y][x-1].getchess()->isredn() == currentcolor)) {
                            //special case for king
                            if (board[y][x].getchess()->getpower() == 8) {
                                //is a king!
                                //if it is not a pawn, then it is capturable.
                                if (!(board[y][x-1].getchess()->getpower() == 1)) {
                                    options++;
                                    cout << "(-1,0)" << endl;
                                }
                            }
                            //special case for pawn
                            else if (board[y][x].getchess()->getpower() == 1) {
                                //is only valid if its another pawn OR a king.
                                if (board[y][x-1].getchess()->getpower() == 8 || board[y][x-1].getchess()->getpower() == 1) {
                                    options++;
                                    cout << "(-1,0)" << endl;
                                }
                            }
                            else {
                                if (board[y][x].getchess()->getpower() >= board[y][x-1].getchess()->getdefense()) {
                                    options++;
                                    cout << "(-1,0)" << endl;
                                }
                            }

                            //if it reached here, it is invalid.




                        }
                    }
                }

                //right!
                if (!(x == 8)) {
                    //if its not empty
                    if (!(board[y][x].isEmpty())) {
                        //if the piece is the opposite color and capturable
                        if (!(board[y][x + 1].getchess()->isredn() == currentcolor)) {
                            //special case for king
                            if (board[y][x].getchess()->getpower() == 8) {
                                //is a king!
                                //if it is not a pawn, then it is capturable.
                                if (!(board[y][x + 1].getchess()->getpower() == 1)) {
                                    options++;
                                    cout << "(1,0)" << endl;
                                }
                            }
                            //special case for pawn
                            else if (board[y][x].getchess()->getpower() == 1) {
                                //is only valid if its another pawn OR a king.
                                if (board[y][x + 1].getchess()->getpower() == 8 || board[y][x + 1].getchess()->getpower() == 1) {
                                    options++;
                                    cout << "(1,0)" << endl;
                                }
                            }
                            else {
                                if (board[y][x].getchess()->getpower() >= board[y][x + 1].getchess()->getdefense()) {
                                    options++;
                                    cout << "(1,0)" << endl;
                                }
                            }

                            //if it reached here, it is invalid.




                        }
                    }
                }

                //need special case for cannon and capturing code






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

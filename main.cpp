#include <SFML/Graphics.hpp>
#include "grid.h"
#include "pawn.h"
#include "cart.h"
#include "horse.h"
#include "elephant.h"
#include "guard.h"
#include "king.h"
#include "cannon.h"


int main() {
    Grid board[4][8];
    int index = 1, totalElements = 32;
    std::srand(std::time(0));


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
            board[i][j].print();
        }
        cout << endl;
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


#ifndef _5X5X_O_H
#define _5X5X_O_H

#include "BoardGame_Classes.h"
#include <iomanip>
#include <cctype>  // for toupper()
// flag to skip if the winner is detected in the other player turn
bool skip = false;

template <typename T>
class _5_X_O_Board:public Board<T> {
    // To know which player turn
    T current_player;
    // store the winning score for each player
    int x_wins = 0;
    int o_wins = 0;
public:
    _5_X_O_Board ();
    bool update_board (int x , int y , T symbol);
    void display_board () ;
    bool is_win() ;
    bool is_draw();
    bool game_is_over();

};
template <typename T>
class _5x5_X_O_player : public Player<T> {
public:
    _5x5_X_O_player (string name, T symbol);
    void getmove(int& x, int& y) ;

};

template <typename T>
class _5x5_X_O_Random_Player : public RandomPlayer<T>{
public:
    _5x5_X_O_Random_Player (T symbol);
    void getmove(int &x, int &y) ;
};





//--------------------------------------- IMPLEMENTATION

// Constructor for X_O_Board
template <typename T>
_5_X_O_Board<T>::_5_X_O_Board() {
    // Set deminsions
    this->rows = this->columns = 5;
    this->board = new char*[this->rows];
    for (int i = 0; i < this->rows; i++) {
        this->board[i] = new char[this->columns];
        for (int j = 0; j < this->columns; j++) {
            this->board[i][j] = 0;
        }
    }
    this->n_moves = 0;
}
template <typename T>
bool _5_X_O_Board<T>::update_board(int x, int y, T mark) {
    // Only update if move is valid
    if(skip){
        current_player = mark;
        this->n_moves++;
        return true;
    }
    if (!(x < 0 || x >= this->rows || y < 0 || y >= this->columns) && (this->board[x][y] == 0|| mark == 0)) {
        if (mark == 0){
            this->n_moves--;
            this->board[x][y] = 0;
        }
        else {
            this->n_moves++;
            this->board[x][y] = toupper(mark);
        }
        current_player = mark;
        return true;
    }
    return false;
}

// Display the board and the pieces on it
template<typename T>
void _5_X_O_Board<T>::display_board() {
    if (!skip) {
        // Print column headers
        cout << "    ";
        for (int j = 0; j < this->columns; j++) {
            cout << "  " << j << "  ";
        }
        cout << endl;

        cout << "   " << string(this->columns * 5 + 1, '-') << endl;

        // Print each row with row headers
        for (int i = 0; i < this->rows; i++) {
            cout << " " << i << " |";
            for (int j = 0; j < this->columns; j++) {
                char cell = this->board[i][j]; // Cell content
                cout << "  " << (cell == 0 ? ' ' : cell) << " |"; // Use ' ' for empty cells
            }
            cout << endl;
            cout << "   " << string(this->columns * 5 + 1, '-') << endl;
        }
        cout << endl;
    }
}

// Returns true if there is any winner
template <typename T>
bool _5_X_O_Board<T>::is_win() {
    // start checking for the winner when moves exceeds or equal to 24
    if (this->n_moves >= 24) {
        // static to keep the values after the skip
        static int curr_wins, other_wins;
        // condition to skip check for the winner again
        if(!skip){
            curr_wins = 0, other_wins = 0;
            int curr_ctr = 0, other_ctr = 0;
            // margin to skip unnecessary iterations in the diagonal check
            const int margin = 2;

            // Check Rows
            for (int i = 0; i < this->rows; i++) {
                for (int j = 0; j < this->columns; j++) {
                    if (this->board[i][j] == current_player) {
                        curr_ctr++;
                        other_ctr = 0;
                    } else if (this->board[i][j] != 0) {
                        other_ctr++;
                        curr_ctr = 0;
                    } else {
                        curr_ctr = other_ctr = 0;
                    }
                    if (curr_ctr == 3) {
                        curr_wins++;
                        curr_ctr--; // Allow overlapping sequences
                    }
                    if (other_ctr == 3) {
                        other_wins++;
                        other_ctr--; // Allow overlapping sequences
                    }
                }
                curr_ctr = other_ctr = 0;
            }

            // Check Columns
            for (int j = 0; j < this->columns; j++) {
                for (int i = 0; i < this->rows; i++) {
                    if (this->board[i][j] == current_player) {
                        curr_ctr++;
                        other_ctr = 0;
                    } else if (this->board[i][j] != 0) {
                        other_ctr++;
                        curr_ctr = 0;
                    } else {
                        curr_ctr = other_ctr = 0;
                    }
                    if (curr_ctr == 3) {
                        curr_wins++;
                        curr_ctr--; // Allow overlapping sequences
                    }
                    if (other_ctr == 3) {
                        other_wins++;
                        other_ctr--; // Allow overlapping sequences
                    }
                }
                curr_ctr = other_ctr = 0;
            }

            // Check Top-Left to Bottom-Right Diagonals
            for (int i = 0; i <= this->rows - 3; i++) {
                for (int j = 0; j <= this->columns - 3; j++) {
                    curr_ctr = other_ctr = 0;
                    for (int k = 0; k < 3; k++) {
                        if (this->board[i + k][j + k] == current_player) {
                            curr_ctr++;
                        } else if (this->board[i + k][j + k] != 0) {
                            other_ctr++;
                        }
                    }
                    if (curr_ctr == 3) {
                        curr_wins++;
                    }
                    if (other_ctr == 3) {
                        other_wins++;
                    }
                }
            }

            // Check Bottom-Left to Top-Right Diagonals
            for (int i = this->rows - 1; i >= 2; i--) {
                for (int j = 0; j <= this->columns - 3; j++) {
                    curr_ctr = other_ctr = 0;
                    for (int k = 0; k < 3; k++) {
                        if (this->board[i - k][j + k] == current_player) {
                            curr_ctr++;
                        } else if (this->board[i - k][j + k] != 0) {
                            other_ctr++;
                        }
                    }
                    if (curr_ctr == 3) {
                        curr_wins++;
                    }
                    if (other_ctr == 3) {
                        other_wins++;
                    }
                }
            }
            // according to the current player, assign no. of wins ti the suitable player
            if(current_player == 'X'){
                this->x_wins = curr_wins;
                this->o_wins = other_wins;
            }else{
                this->x_wins = other_wins;
                this->o_wins = curr_wins;
            }
        }
        // Compare Wins
        // when current wins smaller than the other wins, we need to skip to anounce the right winner
        if(curr_wins < other_wins){
            skip = true;
            int temp;
            temp = curr_wins;
            curr_wins = other_wins;
            other_wins = temp;
            return false;
        }else if(curr_wins > other_wins){
            cout << "With " << curr_wins << " wins, ";
            return true;
        }
    }
    return false;
}


// Return true if 24 moves are done and no winner
template <typename T>
bool _5_X_O_Board<T>::is_draw() {
    if(this->n_moves >= 24 && this->x_wins == this->o_wins){
        cout << "With " << x_wins << " wins for both players, the game is ";
        return true;
    }else{
        return false;
    }
}

template <typename T>
bool _5_X_O_Board<T>::game_is_over() {
    return this->n_moves == 25;
}

//--------------------------------------

// Constructor for _5x5_X_O_player
template <typename T>
_5x5_X_O_player<T>::_5x5_X_O_player(string name, T symbol) : Player<T>(name, symbol) {}

template <typename T>
void _5x5_X_O_player<T>::getmove(int& x, int& y) {
    if(!skip){
        cout << "\nPlease enter your move x and y (0 to 4) separated by spaces: ";
        cin >> x >> y;
    }
}

// Constructor for _5x5_X_O_Random_Player
template <typename T>
_5x5_X_O_Random_Player<T>::_5x5_X_O_Random_Player(T symbol) : RandomPlayer<T>(symbol) {
    this->dimension = 5;
    this->name = "Random Computer Player";
    srand(static_cast<unsigned int>(time(0)));  // Seed the random number generator
}

template <typename T>
void _5x5_X_O_Random_Player<T>::getmove(int& x, int& y) {
    if(!skip){
        x = rand() % this->dimension;  // Random number between 0 and 4
        y = rand() % this->dimension;
    }
}

#endif //_3X3X_O_H


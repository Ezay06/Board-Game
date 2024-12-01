
#ifndef _PYRAMIDIC_X_O_H
#define _PYRAMIDIC_X_O_H

#include "BoardGame_Classes.h"

template <typename T>
class Pyramid_Board : public Board<T> {
    public:
    Pyramid_Board();
    bool update_board(int x, int y, T symbol);
    void display_board();
    bool is_win();
    bool is_draw();
    bool game_is_over();

};

template <typename T>
class Pyramid_Player : public Player<T> {
    public:
    Pyramid_Player(string name, T symbol);
    void getmove(int& x, int& y);

};

template <typename T>
class Random_Pyramid_Player : public RandomPlayer<T> {
    public:
    Random_Pyramid_Player(T symbol);
    void getmove(int& x, int& y);

};






#include <iostream>
#include <iomanip>
#include <cctype>
using namespace std;


template <typename T>
Pyramid_Board<T>::Pyramid_Board(){
    this->rows = this->columns = 5;
    this->board = new char*[this->rows];
    for (int i = 0; i < this->rows; i++){
        this->board[i] = new char[this->columns];
        for (int j = 0; i < this->columns; j++){
            this->board[i][j] = 0;
        }
    }
    this->n_moves = 0;
}

template <typename T>
bool Pyramid_Board<T>::update_board(int x, int y, T mark){
    if (!((x == 0 && y == 0) || (x == 0 && y == 1) || (x == 0 && y == 3) ||
    (x == 0 && y == 4) || (x == 1 && y == 0) || (x == 1 && y == 4) || 
    (x < 0 || x >= this->rows || y < 0 || y >= this->columns)) && this->board[x][y] == 0){
        this->n_moves++;
        this->board[x][y] = toupper(mark);
        return true;
    }

    return false;
}

template <typename T>
void Pyramid_Board<T>::display_board(){
    for (int i = 0; i < this->rows; i++) {
        if (i == 0){
            cout << "\n                      | ";
            cout << "(" << i << "," << 2 << ")";
            cout << setw(2) << this->board[i][j] << " |";
            cout << "\n-----------------------------";
        }

        else if (i == 1){
            cout << "\n           | ";
            for (int j = 1; j < 4; j++) {
                cout << "(" << i << "," << j << ")";
                cout << setw(2) << this->board[i][j] << " |";
                cout << "\n-----------------------------";
            }
        }

        else if (i == 2){
            cout << "\n| ";
            for (int j = 0; j < this->columns; j++) {
                cout << "(" << i << "," << j << ")";
                cout << setw(2) << this->board[i][j] << " |";
                cout << "\n-----------------------------";
            }       
        }

    }    
    cout << endl;
}

template <typename T>
bool Pyramid_Board<T>::is_win(){
    //Check center column
    if (this->board[0][2] == this->board[1][2] && this->board[0][2] == this->board[2,2] && this->board[0][2] != 0){
        return true;
    }

    //Check diagonals
    if (((this->board[0][2] == this->board[1][1] && this->board[0][2] == this->board[2][0]) ||
    (this->board[0][2] == this->board[1][3] && this->board[0][2] == this->board[2][4])) && this->board[0][2] != 0){
        return true
    }

    //Check second row
    if (this->board[1][1] == this->board[1][2] && this->board[1][1] == this->board[1][3] && this->board[1][1] != 0){
        return true
    }

    //Check third row
    if (((this->board[2][0] == this->board[2][1] && this->board[2][0] == this->board[2][2]) && this->board[2][0] != 0) ||
    ((this->board[2][1] == this->board[2][2] && this->board[2][1] == this->board[2][3]) && this->board[2][1] != 0) ||
    (this->board[2][2] == this->board[2][3] && this->board[2][2] == this->board[2][4]) && this->board[2][2] != 0){
        return true;
    }

    return false;
}

template <typename T>
bool Pyramid_Board<T>::is_draw(){
    if (this->n_moves == 9 && !this->is_win()){
        return true;
    }

    return false;
}

template<typename T>
bool Pyramid_Board<T>::game_is_over(){
    return this->is_draw() || this->is_win();
}



template <typename T>
Pyramid_Player<T>::Pyramid_Player(string name, T symbol) : Player<T>(name, symbol){}

template <typename T>
void Pyramid_Player<T>::getmove(int& x, int& y){
    cout << "\nEnter the coordinates of your move seperated by spaces (eg. 2 2). 0 0, 0 1, 0 3, 0 4, 1 0, 1 4 are invalid: ";
    cin >> x >> y;
}



template <typename T>
Random_Pyramid_Player<T>::Random_Pyramid_Player(T symbol) : RandomPlayer<T>(symbol){
    this->dimension = 5;
    this->name = "Random Computer Player";
    srand(static_cast<unsigned int>(time(0)));
}

template <typename T>
void Random_Pyramid_Player<T>::getmove(int& x, int& y){
    x = rand() % this->dimension;
    y = rand() % this->dimension;
}

#endif
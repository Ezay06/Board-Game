#ifndef _FOURINROW_H
#define _FOURINROW_H

#include "BoardGame_Classes.h"
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <vector>

using namespace std;

template <typename T>
class FourInRowBoard : public Board<T>
{
public:
    FourInRowBoard();
    bool update_board(int x, int y, T symbol);
    void display_board();
    bool is_column_available(int y);
    bool is_win();
    bool is_draw();
    bool game_is_over();
};

template <typename T>
class FourInRowPlayer : public Player<T>
{
public:
    FourInRowPlayer(string name, T symbol);
    void getmove(int &x, int &y);
};

template <typename T>
class Random_FourInRowPlayer : public RandomPlayer<T>
{
public:
    Random_FourInRowPlayer(T symbol);
    void getmove(int &x, int &y) override;
};

//--------------------------------------- IMPLEMENTATION------------------------------------------

// Constructor for FourInRowBoard
template <typename T>
FourInRowBoard<T>::FourInRowBoard()
{
    this->rows = 6;
    this->columns = 7;
    this->board = new T *[this->rows];
    for (int i = 0; i < this->rows; i++)
    {
        this->board[i] = new T[this->columns];
        for (int j = 0; j < this->columns; j++)
        {
            this->board[i][j] = '-';
        }
    }
    this->n_moves = 0;
}

template <typename T>
bool FourInRowBoard<T>::is_column_available(int y)
{

    for (int i = this->rows - 1; i >= 0; i--)
    {
        if (this->board[i][y] == '-')
        {
            return true;
        }
    }
    return false;
}

template <typename T>
bool FourInRowBoard<T>::update_board(int x, int y, T symbol)
{
    if (y < 0 || y >= this->columns)
    {
        return false;
    }

    for (int i = this->rows - 1; i >= 0; i--)
    {
        if (this->board[i][y] == '-')
        {
            this->board[i][y] = symbol;
            x = i;
            this->n_moves++;
            return true;
        }
    }

    return false;
}

// Display the board
template <typename T>
void FourInRowBoard<T>::display_board()
{
    cout << "  ";
    // Display column index
    for (int j = 0; j < this->columns; j++)
    {
        cout << j << "   ";
    }
    cout << endl;

    // Display the board
    for (int i = 0; i < this->rows; i++)
    {
        cout << "| ";
        for (int j = 0; j < this->columns; j++)
        {
            cout << this->board[i][j] << " | ";
        }
        cout << endl;
        cout << "-----------------------------" << endl;
    }
}

template <typename T>
bool FourInRowBoard<T>::is_win()
{
    // Horizontal
    for (int i = 0; i < this->rows; i++)
    {
        for (int j = 0; j < this->columns - 3; j++)
        {
            if (this->board[i][j] != '-' && this->board[i][j] == this->board[i][j + 1] && this->board[i][j] == this->board[i][j + 2] && this->board[i][j] == this->board[i][j + 3])
            {
                return true;
            }
        }
    }

    // Vertical =
    for (int i = 0; i < this->rows - 3; i++)
    {
        for (int j = 0; j < this->columns; j++)
        {
            if (this->board[i][j] != '-' && this->board[i][j] == this->board[i + 1][j] && this->board[i][j] == this->board[i + 2][j] && this->board[i][j] == this->board[i + 3][j])
            {
                return true;
            }
        }
    }

    // Diagonal
    for (int i = 0; i < this->rows - 3; i++)
    {
        for (int j = 0; j < this->columns - 3; j++)
        {
            if (this->board[i][j] != '-' && this->board[i][j] == this->board[i + 1][j + 1] && this->board[i][j] == this->board[i + 2][j + 2] && this->board[i][j] == this->board[i + 3][j + 3])
            {
                return true;
            }
        }
    }

    // Diagonal
    for (int i = 3; i < this->rows; i++)
    {
        for (int j = 0; j < this->columns - 3; j++)
        {
            if (this->board[i][j] != '-' && this->board[i][j] == this->board[i - 1][j + 1] && this->board[i][j] == this->board[i - 2][j + 2] && this->board[i][j] == this->board[i - 3][j + 3])
            {
                return true;
            }
        }
    }

    return false;
}

// Check if draw
template <typename T>
bool FourInRowBoard<T>::is_draw()
{
    return this->n_moves == this->rows * this->columns && !is_win();
}

// Check if game is over
template <typename T>
bool FourInRowBoard<T>::game_is_over()
{
    return is_win() || is_draw();
}

// Constructor for FourInRowPlayer
template <typename T>
FourInRowPlayer<T>::FourInRowPlayer(string name, T symbol) : Player<T>(name, symbol) {}

template <typename T>
void FourInRowPlayer<T>::getmove(int &x, int &y)
{
    bool valid = false;
    while (!valid)
    {
        cout << this->getname() << ", enter column (0 to 6): ";
        cin >> y;
        FourInRowBoard<T> *fourInRowBoard = dynamic_cast<FourInRowBoard<T> *>(this->boardPtr);

        valid = fourInRowBoard->is_column_available(y);

        if (!valid)
        {
            cout << "Invalid move! Try again.\n";
        }
    }
}

// Constructor for Random_FourInRowPlayer
template <typename T>
Random_FourInRowPlayer<T>::Random_FourInRowPlayer(T symbol) : RandomPlayer<T>(symbol) {}

template <typename T>
void Random_FourInRowPlayer<T>::getmove(int &x, int &y)
{
    bool valid = false;
    srand(time(0));

    while (!valid)
    {
        y = rand() % 7;

        FourInRowBoard<T> *fourInRowBoard = dynamic_cast<FourInRowBoard<T> *>(this->boardPtr);

        valid = fourInRowBoard->is_column_available(y);

        if (!valid)
        {
            cout << "Invalid move. Trying again...\n";
        }
    }

    cout << "Radnom Computer chose column " << y << endl;
}

#endif
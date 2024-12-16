#ifndef _3X3_NUM_TICTACTOE_H
#define _3X3_NUM_TICTACTOE_H

#include "BoardGame_Classes.h"
#include <iostream>
#include <iomanip>
#include <algorithm>

using namespace std;

template <typename T>
class NumBoard : public Board<T>
{
public:
    NumBoard();
    bool update_board(int x, int y, T symbol);
    void display_board();
    bool is_win();
    bool is_draw();
    bool game_is_over();
    bool is_cell_empty(int x, int y) const;
};

template <typename T>
class NumPlayer : public Player<T>
{
private:
    vector<T> allowed_nums;

public:
    NumPlayer(string name, vector<T> nums);
    void getmove(int &x, int &y);
};

template <typename T>
class Random_NumPlayer : public RandomPlayer<T>
{
private:
    vector<T> allowed_nums;

public:
    Random_NumPlayer(vector<T> nums);
    void getmove(int &x, int &y) override;
};

//--------------------------------------- IMPLEMENTATION

// Constructor for NumBoard
template <typename T>
NumBoard<T>::NumBoard()
{
    this->rows = this->columns = 3;
    this->board = new int *[this->rows];
    for (int i = 0; i < this->rows; i++)
    {
        this->board[i] = new int[this->columns];
        for (int j = 0; j < this->columns; j++)
        {
            this->board[i][j] = 0;
        }
    }
    this->n_moves = 0;
}

// Update board with the player's number
template <typename T>
bool NumBoard<T>::update_board(int x, int y, T symbol)
{
    // Only update if move is valid
    if (!(x < 0 || x >= this->rows || y < 0 || y >= this->columns) && (this->board[x][y] == 0))
    {

        this->n_moves++;
        this->board[x][y] = symbol;
        return true;
    }
    return false;
}

// Display board
template <typename T>
void NumBoard<T>::display_board()
{
    for (int i = 0; i < this->rows; i++)
    {
        cout << "\n| ";
        for (int j = 0; j < this->columns; j++)
        {
            cout << "(" << i << "," << j << ")";
            cout << setw(2) << this->board[i][j] << " |";
        }
        cout << "\n-----------------------------";
    }
    cout << endl;
}

template <typename T>
bool NumBoard<T>::is_cell_empty(int x, int y) const
{
    if (x < 0 || x >= this->rows || y < 0 || y >= this->columns)
    {
        return false;
    }
    return this->board[x][y] == 0;
}

// Chech winner
template <typename T>
bool NumBoard<T>::is_win()
{
    for (int i = 0; i < this->rows; i++)
    {
        if (this->board[i][0] != 0 && this->board[i][1] != 0 && this->board[i][2] != 0 &&
            (this->board[i][0] + this->board[i][1] + this->board[i][2] == 15))
        {
            return true;
        }
    }

    // Check columns
    for (int i = 0; i < this->columns; i++)
    {
        if (this->board[0][i] != 0 && this->board[1][i] != 0 && this->board[2][i] != 0 &&
            (this->board[0][i] + this->board[1][i] + this->board[2][i] == 15))
        {
            return true;
        }
    }

    // Check diagonals
    if (this->board[0][0] != 0 && this->board[1][1] != 0 && this->board[2][2] != 0 &&
        (this->board[0][0] + this->board[1][1] + this->board[2][2] == 15))
    {
        return true;
    }

    if (this->board[0][2] != 0 && this->board[1][1] != 0 && this->board[2][0] != 0 &&
        (this->board[0][2] + this->board[1][1] + this->board[2][0] == 15))
    {
        return true;
    }

    return false;
}

// Return true if 9 moves are done and no winner
template <typename T>
bool NumBoard<T>::is_draw()
{
    return (this->n_moves == 9 && !is_win());
}

template <typename T>
bool NumBoard<T>::game_is_over()
{
    return is_win() || is_draw();
}

// NumPlayer constructor
template <typename T>
NumPlayer<T>::NumPlayer(string name, vector<T> nums) : Player<T>(name, 0)
{
    this->allowed_nums = nums;
}

template <typename T>
void NumPlayer<T>::getmove(int &x, int &y)
{
    bool valid = false;
    int choice;
    auto board = static_cast<NumBoard<T> *>(this->boardPtr);

    while (!valid)
    {
        cout << this->getname() << " Choose a number from your available numbers: ";
        for (int n : allowed_nums)
        {
            cout << n << " ";
        }
        cout << endl;
        cin >> choice;

        if (cin.fail())
        {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid input. Please enter a valid integer." << endl;
            continue;
        }

        auto it = find(allowed_nums.begin(), allowed_nums.end(), choice);
        if (it == allowed_nums.end())
        {
            cout << "Invalid choice, try again.\n";
            continue;
        }

        cout << "\nEnter the coordinates for your move (x y): ";
        cin >> x >> y;

        if (cin.fail())
        {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid input. Please enter a valid integer." << endl;
            continue;
        }

        if (x < 0 || x >= 3 || y < 0 || y >= 3)
        {
            cout << "Out of range. Try again.\n";
            continue;
        }

        if (!board->is_cell_empty(x, y))
        {
            cout << "Cell occupied. Try again.\n";
            continue;
        }

        this->symbol = choice;
        allowed_nums.erase(it);
        valid = true;
    }
}

template <typename T>
Random_NumPlayer<T>::Random_NumPlayer(vector<T> nums) : RandomPlayer<T>(0)
{
    this->allowed_nums = nums;
}

template <typename T>
void Random_NumPlayer<T>::getmove(int &x, int &y)
{
    bool valid = false;
    srand(time(0));
    auto board = static_cast<NumBoard<T> *>(this->boardPtr);

    while (!valid)
    {
        int choice = allowed_nums[rand() % allowed_nums.size()];
        x = rand() % 3;
        y = rand() % 3;

        if (board->is_cell_empty(x, y))
        {

            this->symbol = choice;
            auto it = find(allowed_nums.begin(), allowed_nums.end(), choice);
            if (it != allowed_nums.end())
            {
                allowed_nums.erase(it);
            }
            valid = true;
            cout << "Random computer chose number: " << choice << " and position (" << x << ", " << y << ")\n";
        }
    }
}

#endif
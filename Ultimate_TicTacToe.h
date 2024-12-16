#ifndef ULTIMATE_TIC_TAC_TOE_H
#define ULTIMATE_TIC_TAC_TOE_H

#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include "BoardGame_Classes.h"

using namespace std;

template <typename T>
class Ultimate_Board : public Board<T>
{
private:
    vector<vector<vector<T>>> ultimateBoard;
    vector<vector<T>> mainBoard;

public:
    Ultimate_Board();
    void display_board() override;
    bool update_board(int x, int y, T symbol) override;
    bool chech_win_sub(vector<T> &board, T symbol);
    bool chech_draw(vector<T> &board);
    bool check_win_main();
    bool is_win() override;
    bool is_draw() override;
    bool game_is_over() override;
};

template <typename T>
class Ultimate_Player : public Player<T>
{
public:
    Ultimate_Player(string n, T symbol);
    void getmove(int &x, int &y) override;
};

template <typename T>
class Ultimate_RandomPlayer : public RandomPlayer<T>
{
public:
    Ultimate_RandomPlayer(T symbol);
    void getmove(int &x, int &y) override;
};

//----------------------------------Implementation----------------------------------

template <typename T>
Ultimate_Board<T>::Ultimate_Board()
{
    ultimateBoard.resize(3, vector<vector<T>>(3, vector<T>(9, ' ')));
    mainBoard.resize(3, vector<T>(3, ' '));
}

template <typename T>
void Ultimate_Board<T>::display_board()
{
    const int cellW = 4;

    // Displaying the subboards
    cout << "\nUltimate Board:\n";
    for (int bRow = 0; bRow < 3; ++bRow)
    {
        for (int sRow = 0; sRow < 3; ++sRow)
        {
            for (int bCol = 0; bCol < 3; ++bCol)
            {
                for (int sCol = 0; sCol < 3; ++sCol)
                {
                    int gRow = bRow * 3 + sRow;
                    int gCol = bCol * 3 + sCol;
                    T cell = ultimateBoard[bRow][bCol][sRow * 3 + sCol];

                    if (cell == ' ')
                    {
                        cout << setw(cellW) << "(" + to_string(gRow) + "," + to_string(gCol) + ")";
                    }

                    else
                    {
                        cout << setw(cellW) << " " << cell << " ";
                    }

                    if (sCol < 2)
                    {
                        cout << " ";
                    }
                }

                if (bCol < 2)
                {
                    cout << " || ";
                }
            }
            cout << endl;

            if (sRow == 2 && bRow < 2)
            {
                cout << string(65, '=') << endl;
            }
        }
    }

    // Display the main board
    cout << "\nMain Board:\n";

    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {

            if (mainBoard[i][j] == ' ')
                cout << setw(cellW) << "-";
            else
                cout << setw(cellW) << " " << mainBoard[i][j] << " ";

            if (j < 2)
                cout << "|";
        }
        cout << endl;

        if (i < 2)
            cout << string(cellW * 3 + 2, '-') << endl;
    }
}

template <typename T>
bool Ultimate_Board<T>::update_board(int x, int y, T symbol)
{
    int subRow = x / 3;
    int subCol = y / 3;
    int cellIdx = (x % 3) * 3 + (y % 3);

    if (ultimateBoard[subRow][subCol][cellIdx] == ' ')
    {
        ultimateBoard[subRow][subCol][cellIdx] = symbol;

        // Check sub-board is won
        if (chech_win_sub(ultimateBoard[subRow][subCol], symbol))
        {
            mainBoard[subRow][subCol] = symbol;
        }

        // Check sub-board is draw
        if (chech_draw(ultimateBoard[subRow][subCol]) && mainBoard[subRow][subCol] == ' ')
        {
            mainBoard[subRow][subCol] = 'D';
        }

        return true;
    }
    return false;
}

template <typename T>
bool Ultimate_Board<T>::chech_win_sub(vector<T> &board, T symbol)
{
    for (int i = 0; i < 3; i++)
    {
        if (board[i * 3] == symbol && board[i * 3 + 1] == symbol && board[i * 3 + 2] == symbol)
        {
            return true;
        }
        if (board[i] == symbol && board[i + 3] == symbol && board[i + 2 * 3] == symbol)
        {
            return true;
        }
    }
    if (board[0] == symbol && board[4] == symbol && board[8] == symbol)
    {
        return true;
    }
    if (board[2] == symbol && board[4] == symbol && board[6] == symbol)
    {
        return true;
    }
    return false;
}

template <typename T>
bool Ultimate_Board<T>::chech_draw(vector<T> &board)
{
    for (T cell : board)
    {
        if (cell != 'X' && cell != 'O')
            return false;
    }
    return true;
}

template <typename T>
bool Ultimate_Board<T>::check_win_main()
{
    for (int i = 0; i < 3; i++)
    {
        if (mainBoard[i][0] == mainBoard[i][1] && mainBoard[i][1] == mainBoard[i][2] && mainBoard[i][0] != ' ')
        {
            return true;
        }
        if (mainBoard[0][i] == mainBoard[1][i] && mainBoard[1][i] == mainBoard[2][i] && mainBoard[0][i] != ' ')
        {
            return true;
        }
    }
    if (mainBoard[0][0] == mainBoard[1][1] && mainBoard[1][1] == mainBoard[2][2] && mainBoard[0][0] != ' ')
    {
        return true;
    }
    if (mainBoard[0][2] == mainBoard[1][1] && mainBoard[1][1] == mainBoard[2][0] && mainBoard[0][2] != ' ')
    {
        return true;
    }
    return false;
}

template <typename T>
bool Ultimate_Board<T>::is_win()
{
    return check_win_main();
}

template <typename T>
bool Ultimate_Board<T>::is_draw()
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (mainBoard[i][j] == ' ')
            {
                return false;
            }
        }
    }
    return true;
}

template <typename T>
bool Ultimate_Board<T>::game_is_over()
{
    return is_win() || is_draw();
}

// Human Player
template <typename T>
Ultimate_Player<T>::Ultimate_Player(string n, T symbol) : Player<T>(n, symbol) {}

template <typename T>
void Ultimate_Player<T>::getmove(int &x, int &y)
{
    while (true)
    {
        cout << this->name << "'s turn. Enter cooridinates 2 numbers (0-8) separated by spaces : ";
        cin >> x >> y;

        if (x < 0 || x > 8 || y < 0 || y > 8)
        {
            cout << "Invalid input. Coordinates must be between 0 and 8. Try again.\n";
            cin.clear();
            cin.ignore(1000, '\n');
        }
        else
        {
            break;
        }
    }
}

// Random Player
template <typename T>
Ultimate_RandomPlayer<T>::Ultimate_RandomPlayer(T symbol) : RandomPlayer<T>(symbol)
{
    srand(static_cast<unsigned int>(time(0)));
}

template <typename T>
void Ultimate_RandomPlayer<T>::getmove(int &x, int &y)
{
    x = rand() % 9;
    y = rand() % 9;
}

#endif

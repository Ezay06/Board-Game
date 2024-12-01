#ifndef WORD_TTO
#define wORD_TTO

#include "BoardGame_Classes.h"
#include <iostream>
#include <unordered_set>
#include <cctype>
#include <string>
#include <fstream>
#include <random>
using namespace std;


template <typename T>
class Word_Board : public Board<T>{
    protected:
    unordered_set<string> correct_words;
    public:
    Word_Board();
    bool update_board(int x, int y, T symbol);
    void display_board();
    bool is_win();
    bool is_draw();
    bool game_is_over();

};

template <typename T>
class Word_Player : public Player<T>{
    public:
    Word_Player(string name);
    void getmove(int& x, int& y);

};

template <typename T>
class Random_Word_Player : public RandomPlayer<T>{
    public:
    Random_Word_Player();
    void getmove(int& x, int& y);
};







template <typename T>
Word_Board<T>::Word_Board(){
    this->rows = this->columns = 3;
    this->board = new char*[this->rows];
    for(int i = 0; i < this->rows; i++){
        this->board[i] = new char[this->columns];
        for(int j = 0; i < this->columns; j++){
            this->board[i][j] = 0;
        }
    }

    ifstream words("dic.txt");
    string word;
    while(words >> word){
        correct_words.insert(word);
    }
}

template <typename T>
bool Word_Board<T>::update_board(int x, int y, T mark){
    if (!((x < 0 || x >=this->rows) || (y < 0 || y >= this->columns)) && this->board[x][y] == 0){
        this->n_moves++;
        this->board[x][y] = toupper(mark);
        return true;
    }

    return false;
}

template <typename T>
void Word_Board<T>::display_board(){
    for (int i = 0; i < this->rows; i++) {
        cout << "\n| ";
        for (int j = 0; j < this->columns; j++) {
            cout << "(" << i << "," << j << ")";
            cout << setw(2) << this->board[i][j] << " |";
        }
        cout << "\n-----------------------------";
    }
    cout << endl;
}

template <typename T>
bool Word_Board<T>::is_win(){
    string word;
    pair<typename unordered_set<string>::iteraotor, bool> result;
    //Check rows
    for (int i = 0; i < this->rows; i++){
        word += this->board[i][0]; word += this->board[i][1]; word += this->board[i][2];
        result = correct_words.insert(word);
        if (!result.second){
            return true;
        }

        else{
            correct_words.erase(result.first);
            word = "";
        }


        word += this->board[i][2]; word += this->board[i][1]; word += this->board[i][0];
        result = correct_words.insert(word);
        if (!result.second){
            return true;
        }

        else{
            correct_words.erase(result.first);
            word = "";
        }
    }

    //Check columns
    for (int i = 0; i < this->columns; i++){
        word += this->board[0][i]; word += this->board[1][i]; word += this->board[i][2];
        result = correct_words.insert(word);
        if (!result.second){
            return true;
        }

        else{
            correct_words.erase(result.first);
            word = "";
        }


        word += this->board[2][i]; word += this->board[1][i]; word += this->board[0][i];
        result = correct_words.insert(word);
        if (!result.second){
            return true;
        }

        else{
            correct_words.erase(result.first);
            word = "";
        }
    }

    //Check diagonals
    word += this->board[0][0]; word += this->board[1][1]; word += this->board[2][2];
    result = correct_words.insert(word);
    if (!result.second){
        return true;
    }

    else{
        correct_words.erase(result.first);
        word = "";
    }

    word += this->board[2][2]; word += this->board[1][1]; word += this->board[0][0];
    result = correct_words.insert(word);
    if (!result.second){
        return true;
    }

    else{
        correct_words.erase(result.first);
        word = "";
    }



    word += this->board[2][0]; word += this->board[1][1]; word += this->board[0][2];
    result = correct_words.insert(word);
    if (!result.second){
        return true;
    }

    else{
        correct_words.erase(result.first);
        word = "";
    }

    word += this->board[0][2]; word += this->board[1][1]; word += this->board[2][0];
    result = correct_words.insert(word);
    if (!result.second){
        return true;
    }

    else{
        correct_words.erase(result.first);
        word = "";
    }

    return false;

}

template <typename T>
bool Word_Board<T>::is_draw(){
    if (this->n_moves == 9 && !this->is_win()){
        return true;
    }

    return false;
}

template <typename T>
bool Word_Board<T>::game_is_over(){
    return this->is_win() || this->is_draw();
}



template <typename T>
Word_Player<T>::Word_Player(string name) : Player<T>(name, 0){}

template <typename T>
void Word_Player<T>::getmove(int& x, int& y){
    cout << "\nEnter the coordinates of your move and the letter you want to add seperated by spaces (eg. 0 0 a): ";
    cin >> x >> y >> this->symbol;
}



template <typename T>
Random_Word_Player<T>::Random_Word_Player() : RandomPlayer<T>(0){
    this->dimension = 3;
    this->name = "Random Computer Player";
    srand(static_cast<unsigned int>(time(0)));
}

template <typename T>
void Random_Word_Player<T>::getmove(int& x, int& y){
    x = rand() % this->dimension;
    y = rand() % this->dimension;


    std::random_device rd;
    std::mt19937 gen(rd()); 

    uniform_int_distribution<> distrib(65, 90);

    this->symbol = distrib(gen);
}


#endif